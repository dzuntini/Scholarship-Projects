import { Injectable, Logger } from '@nestjs/common';
import { Socket, Server } from 'socket.io';
import {
  WebSocketGateway,
  OnGatewayInit,
  OnGatewayConnection,
  WebSocketServer,
  SubscribeMessage,
} from '@nestjs/websockets';
import { SocketService } from './socket.service';
import { BeLike, AskedFormular, GameService } from './game/game.service';
import { ChatService } from './chat/chat.service';
import { GameType } from './game/game.dto';

@WebSocketGateway(3001, { cors: true, namespace: 'socket.io' })
@Injectable()
export class SsgGateway implements OnGatewayInit, OnGatewayConnection {
  private logger: Logger = new Logger('SsgGateway');

  @WebSocketServer() wss: Server;
  // eslint-disable-next-line @typescript-eslint/no-empty-function
  constructor(
    private readonly socketService: SocketService,
    private readonly gameService: GameService,
    private readonly chatService: ChatService,
  ) {}

  ////
  //// SOCKET SERVICE INTERACTIONS
  ////

  async afterInit() {
    await this.socketService.setSocketService(
      this.logger,
      this.wss,
      this.gameService,
      this.chatService,
    );
    await new Promise((r) => setTimeout(r, 2000));
    this.wss.emit('refresh-client-list');
    // this.logger.log('Websocket gateway initialized');
  }

  handleConnection(client: Socket) {
    this.socketService.connect(client);
  }

  handleDisconnect(client: Socket) {
    this.socketService.disconnect(client);
  }

  @SubscribeMessage('Logout')
  logout(client: Socket) {
    this.socketService.logout(client);
  }

  @SubscribeMessage('get-status')
  getStatus(client: Socket, data: any) {
    this.socketService.getStatus(client, data);
  }

  ////
  //// GAME SERVICE INTERACTIONS
  ////

  @SubscribeMessage('LeaveGame')
  leaveGame(client: Socket) {
    this.gameService.GameIssue(client, false);
  }

  @SubscribeMessage('StartGame')
  startGame(client: Socket, data: AskedFormular) {
    this.gameService.startGame(client, data);
  }

  //@SubscribeMessage('freeGames')
  //freeMapGame(client: Socket) {
  //  this.gameService.freeGames(client);
  //}

  @SubscribeMessage('pressKey')
  pressKey(client: Socket, data: any) {
    this.gameService.pressKey(client, data);
  }

  @SubscribeMessage('realeaseKey')
  realeaseKey(client: Socket, data: any) {
    this.gameService.realeaseKey(client, data);
  }

  @SubscribeMessage('playAs')
  playAs(
    client: Socket,
    data: {
      beLike: BeLike;
      gameUUID: string;
      gameType: undefined | GameType;
    },
  ) {
    this.gameService.playAs(
      client,
      !data.beLike ? BeLike.Spectator : BeLike.Player,
      data.gameUUID,
      !data.gameType ? GameType.unranked : GameType.ranked,
    );
  }

  @SubscribeMessage('getGamesList')
  getGamesList(client: Socket) {
    this.gameService.getGamesList(client);
  }

  @SubscribeMessage('invitGame')
  InvitGame(client: Socket, data: { guestID: number; gameType: GameType }) {
    this.gameService.InvitGame(client, data.guestID, data.gameType);
  }

  @SubscribeMessage('acceptGame')
  AcceptGame(client: Socket, data: { gameUUID?: string }) {
    this.gameService.AcceptGame(client, data.gameUUID);
  }

  @SubscribeMessage('abandonGame')
  abandonGame(client: Socket) {
    this.gameService.GameIssue(client, false);
  }

  ////
  //// CHAT SERVICE INTERACTIONS
  ////

  @SubscribeMessage('sendMessage')
  sendMessage(client: Socket, data: { message: string; roomID: number }) {
    this.chatService.sendMessage(client, data);
  }

  @SubscribeMessage('connect-chat')
  connectToChat(client: Socket) {
    this.wss.to(client.id).emit('connectedChat');
  }

  @SubscribeMessage('chat-joinroom')
  joinRoom(client: Socket, data: { channelID: number }) {
    this.chatService.joinRoom(client, data.channelID);
  }

  @SubscribeMessage('chat-del-room')
  deleteRoom(client: Socket, data: { id: number; name: string }) {
    this.chatService.deleteRoom(client, data.id, data.name);
  }

  @SubscribeMessage('chat-modify-room')
  modifyRoom(client: Socket, data: { id: number; name: string }) {
    this.chatService.modifyRoom(client, data.id, data.name + '-' + data.id);
  }

  @SubscribeMessage('chat-update-room')
  updateListChatRoom() {
    this.chatService.updateListChatRoom();
  }

  @SubscribeMessage('chat-leave-room')
  leaveChatRoom(client: Socket) {
    this.chatService.leaveRoom(client);
  }

  @SubscribeMessage('update-users')
  updateUsers(client: Socket) {
    this.chatService.updateUsers(client);
  }

  @SubscribeMessage('kicked')
  kickedUser(client: Socket, data: { id: number; roomid: number }) {
    this.chatService.kickedUser(client, data.id, data.roomid);
  }
}
