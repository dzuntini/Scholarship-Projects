import { CrntClient, SocketService } from '../socket.service';
import { Injectable, Logger } from '@nestjs/common';
import { Socket, Server } from 'socket.io';
import { RoomsService } from 'src/rooms/rooms.service';

@Injectable()
export class ChatService {
  private logger: Logger;
  private wss: Server;
  //id; dataBaseName
  private chatRoom: Map<number, string> = new Map<number, string>();
  //id; uuid;
  private clientByRoom: Map<number, string> = new Map<number, string>();
  constructor(
    private readonly socketService: SocketService,
    private readonly roomService: RoomsService,
  ) {}

  addChannel(channelID: number, name: string) {
    this.chatRoom.set(channelID, name);
  }

  async setChatService(logger: Logger, wss: Server) {
    this.logger = logger;
    this.wss = wss;
    const allChannels: any[] = await this.roomService.getAll();
    if (allChannels.length) {
      for (const crnt in allChannels) {
        const channel = allChannels[crnt];
        this.addChannel(channel.id, channel.name);
      }
    }
  }

  setRoomById(client: Socket | number, roomName: string) {
    const clientId =
      typeof client === 'number'
        ? client
        : this.socketService.findClientIDbySocket(client);
    if (clientId !== false && this.getRoomByName(roomName)) {
      this.clientByRoom.set(clientId, roomName);
    }
  }

  leaveRoom(client: Socket) {
    const clientID = this.socketService.findClientIDbySocket(client);
    if (clientID !== false && this.clientByRoom.get(clientID) !== undefined) {
      const channelUUID: string = this.clientByRoom.get(clientID);
      const channelID: number = +channelUUID.split('-').pop();
      client.leave(this.clientByRoom.get(clientID));
      this.wss
        .to(this.clientByRoom.get(clientID))
        .emit('user-status', { channelID: channelID, userID: clientID });
      this.clientByRoom.delete(clientID);
    }
  }

  modifyRoom(client: Socket, roomID: number, newName: string) {
    if (this.socketService.loggedClient(client)) {
      const oldName = this.getRoomById(roomID);
      if (oldName && oldName !== newName) {
        this.wss.to(oldName).socketsJoin(newName);
        this.wss.to(oldName).socketsLeave(oldName);
        for (const [key, value] of this.clientByRoom) {
          if (value === oldName) this.setRoomById(key, newName);
        }
      }
      this.updateListChatRoom();
    }
  }

  async joinRoom(client: Socket, channelID: number) {
    const clientID: CrntClient = this.socketService.loggedClient(client);
    if (!clientID) return;
    const channelUUID: string | false = this.getRoomById(channelID);
    if (!channelUUID) {
      this.socketService.errorMessage(client, "room doesn't exist");
      return;
    }
    const channel: any = await this.roomService.findOne(channelID, clientID);
    const status: number | null = await this.getStatus(channel, clientID);
    if (!status || status === 4 || status === 6) return;
    this.leaveRoom(client);
    this.setRoomById(client, channelUUID);
    client.join(channelUUID);
    this.wss
      .to(channelUUID)
      .emit('user-status', { channelID: channelID, userID: clientID });
    this.wss.to(client.id).emit('rooms-updated');
  }

  deleteRoom(client: Socket, id: number, name: string) {
    if (this.socketService.loggedClient(client)) {
      const oldName: string = name + '-' + id;
      if (oldName !== undefined && oldName !== null) {
        this.wss.to(oldName).emit('reset-draft');
        this.wss.to(oldName).socketsLeave(oldName);
        for (const [key, value] of this.clientByRoom)
          if (value === oldName) this.clientByRoom.delete(key);
      }
      // this.showClientRooms();
      this.updateListChatRoom();
    }
  }

  async kickedUser(client: Socket, userid: number, roomID: number) {
    const clientId = this.socketService.findClientIDbySocket(client);
    const userSocket = this.socketService.findSocketByClientID(userid);
    if (clientId && userSocket) {
      const clientStatus = await this.getStatus(roomID, clientId);
      const userStatus = await this.getStatus(roomID, userid);
      if ((clientStatus === 1 || clientStatus === 2) && userStatus > 3) {
        this.wss.to(userSocket.id).emit('reset-draft');
        this.leaveRoom(userSocket);
        this.wss.to(userSocket.id).emit('reset-draft');
      }
    }
  }

  async sendMessage(
    client: Socket,
    data: { message: string | undefined; roomID: number },
  ) {
    const clientID: CrntClient =
      this.socketService.findClientIDbySocket(client);

    if (!clientID || !data || !data.message) return;
    if ((await this.getStatus(data.roomID, clientID)) === 5) {
      this.wss.to(client.id).emit('fail-join', {
        id: clientID,
        message: "You're Muted! No talking!",
      });
      return;
    }
    if ((await this.getStatus(data.roomID, clientID)) > 3) return;
    const chatUUID: string | undefined = this.clientByRoom.get(clientID);
    if (
      chatUUID !== undefined &&
      (await this.roomService.addMessageToRoom(
        data.roomID,
        clientID,
        data.message,
      )) !== null
    ) {
      this.wss.to(chatUUID).emit('message-received', {
        id: clientID,
        message: data.message,
      });
    }
  }

  getRoomById(id: number): string | false {
    // this.logger.log(id);
    for (const [key, value] of this.chatRoom)
      if (id === key) return value + '-' + id;
    return false;
  }

  getRoomByName(name: string): number | false {
    for (const [key, value] of this.chatRoom)
      if (name === value + '-' + key) return key;
    return false;
  }

  getRoomUUID(roomID: number, roomUUID: string): string | false {
    if (roomID) return this.getRoomById(roomID);
    else {
      for (const [key, value] of this.chatRoom)
        if (roomUUID === value + '-' + key) return roomUUID;
    }
    return false;
  }

  showClientRooms() {
    this.logger.log('Full Clientrooms');
    for (const [key, value] of this.clientByRoom) {
      this.logger.log('Key = ' + key + ' Value = ' + value);
    }
  }

  showChatRooms() {
    this.logger.log('Full Clientrooms');
    for (const [key, value] of this.chatRoom)
      this.logger.log('Key = ' + key + ' Value = ' + value);
  }

  async getStatus(roomInfo: any, userID: number): Promise<number> {
    const room: any =
      typeof roomInfo === 'number'
        ? await this.roomService.findOneBackend(roomInfo)
        : roomInfo;
    // this.logger.log('Members in room');
    // this.logger.log(room);

    if (room !== null) {
      for (let a = 0; room.Access[a]; ++a) {
        if (room.Access[a].appuserID === userID)
          return room.Access[a].AuthorizationID;
      }
    }
    return null;
  }

  updateUsers(client: Socket) {
    const clientId = this.socketService.findClientIDbySocket(client);
    if (clientId !== false && this.clientByRoom.get(clientId) !== undefined) {
      const channelUUID: string = this.clientByRoom.get(clientId);
      const channelID: number = +channelUUID.split('-').pop();
      this.wss
        .to(this.clientByRoom.get(clientId))
        .emit('user-status', { channelID: channelID, userID: clientId });
    }
  }

  async updateListChatRoom() {
    const roomlist = await this.roomService.getAll();
    for (let a = 0; a < roomlist.length; ++a)
      this.chatRoom.set(roomlist[a].id, roomlist[a].name);
    // this.showChatRooms();
    this.wss.emit('rooms-updated');
  }
}
