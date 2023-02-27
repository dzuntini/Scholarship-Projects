import { Injectable, Logger } from '@nestjs/common';
import { Socket, Server } from 'socket.io';
import { JwtService } from 'src/auth/jwt/jwt.service';
import { ChatService } from './chat/chat.service';
import { InGame, ClientInGame, GameService } from './game/game.service';
export type ClientID = number;
export type CrntClient = ClientID | false;

@Injectable()
export class SocketService {
  private logger: Logger;
  private wss: Server;
  private gameService: GameService;
  private chatService: ChatService;
  private clients: Map<number, Socket> = new Map<number, Socket>();

  // eslint-disable-next-line @typescript-eslint/no-empty-function
  constructor(private readonly jwtService: JwtService) {}

  async setSocketService(
    logger: Logger,
    wss: Server,
    gameService: GameService,
    chatService: ChatService,
  ) {
    this.logger = logger;
    this.wss = wss;
    this.gameService = gameService;
    this.chatService = chatService;
    this.gameService.setGameService(this.logger, this.wss);
    await this.chatService.setChatService(this.logger, this.wss);
  }

  errorMessage(client: Socket, errorMessage: string) {
    this.wss.to(client.id).emit('generalErrorMessage', errorMessage);
  }

  connect(client: Socket) {
    // this.logger.log('Client Socket connected');
    client.on('associateIDtoSocket', (data: { token: string | null }) =>
      this.associateIDtoSocket(client, data),
    );
    // this.logger.log('event associate ID to Socket init');
    // this.clients.forEach((key, value) => {
    //  this.logger.log(key.id + ' ' + value.toString());
    // });
  }

  findClientIDbySocket(client: Socket): CrntClient {
    for (const [clientID, value] of this.clients.entries()) {
      if (value === client) {
        return clientID;
      }
    }
    return false;
  }

  findSocketByClientID(clientID: number): Socket | false {
    for (const [clientId, value] of this.clients.entries())
      if (clientId === clientID) return value;
    return false;
  }

  loggedClient(client: Socket): CrntClient {
    const isClient: CrntClient = this.findClientIDbySocket(client);
    if (!isClient) this.errorMessage(client, 'you need to be authenticated');
    return isClient;
  }

  associateIDtoSocket(client: Socket, data: any) {
    let clientID: any = this.findClientIDbySocket(client);
    if (clientID !== false) this.clients.delete(clientID);
    client.removeListener('associateIDtoSocket', () => {
      // this.logger.log('client ' + client.id + ' remove associatedIDtoSocket');
    });
    const user = this.jwtService.decodeToken(data.token);
    if (user !== null && this.jwtService.verifyToken(data.token)) {
      clientID = user.sub;
      if (typeof this.clients.get(clientID) !== 'undefined') {
        this.wss.to(this.clients.get(clientID).id).emit('forceDisconnect');
        this.clients.delete(clientID);
        // client.disconnect(true);
      }
      this.clients.set(clientID, client);
      // this.logger.log(
      //  'client: ' +
      //    this.findClientIDbySocket(client) +
      //    ' associates to his socket',
      // );
      this.wss.emit('client-status-updated', {
        id: user.sub,
        status: 1,
      });
      this.wss.to(client.id).emit('validedAuthentication', {
        validation: 'Authentication valided',
      });
    }
  }

  disconnect(client: Socket) {
    const clientID: CrntClient = this.findClientIDbySocket(client);
    if (clientID !== false) {
      this.gameService.GameIssue(client, false);
      this.chatService.leaveRoom(client);
      this.clients.delete(clientID);
    }
    client.disconnect(true);
  }

  logout(client: Socket) {
    const clientID: CrntClient = this.findClientIDbySocket(client);
    if (clientID !== false) {
      // this.logger.log('Deleteing: ' + clientID + ' ' + client.id);
      this.gameService.GameIssue(client, false);
      this.clients.delete(clientID);
      this.wss.emit('client-status-updated', {
        id: clientID,
        status: 0,
      });
      this.wss.to(client.id).emit('Delogged');
    }
    // this.clients.forEach((key, value) => {
    // this.logger.log(key.id + ' ' + value.toString());
    // });
  }

  getStatus(client: Socket, data: any) {
    const user = this.findSocketByClientID(data.id);
    if (typeof user === 'boolean') {
      this.wss.to(client.id).emit('client-status-updated', {
        id: data.id,
        status: 0,
      });
    } else if (this.gameService.clientInGame(client)) {
      const test: ClientInGame = this.gameService.clientInGame(client);
      // console.log('player is : ' + (test as InGame).player);
      this.wss.to(client.id).emit('client-status-updated', {
        id: data.id,
        status: 2,
      });
      return;
    } else {
      this.wss.to(client.id).emit('client-status-updated', {
        id: data.id,
        status: 1,
      });
    }
  }
}
