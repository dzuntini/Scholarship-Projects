import { Injectable, Logger } from '@nestjs/common';
import { Server, Socket } from 'socket.io';
import { AppusersService } from 'src/appusers/appusers.service';
import { GamesService } from 'src/games/games.service';
import { RoomsService } from 'src/rooms/rooms.service';
import { SocketService, CrntClient } from '../socket.service';
import { GameType, GameInfo, GameStatus, GameRules, GAME } from './game.dto';
import { ChatService } from '../chat/chat.service';

export type InGame = {
  ID: number;
  game: GAME;
  player: number;
};

export type ClientInGame = InGame | false;

export enum BeLike {
  Spectator = 0,
  Player = 1,
}

export type InvitType = {
  hostID: number;
  guestID: number;
};

export type AskedFormular = {
  scoreColor: number;
  boardColor: number;
  wallColor: number;
  player1: number;
  player2: number;
  ballColor: number;
  ballShape: string;
};

type FormularAnswer = {
  scoreColor: string | false;
  boardColor: string | false;
  wallColor: string | false;
  player1: string | false;
  player2: string | false;
  ballColor: string | false;
  ballShape: string | false;
//  special: boolean;
  startButton: boolean;
};

@Injectable()
export class GameService {
  private logger: Logger;
  private wss: Server;
  private games: Map<string, GAME> = new Map<string, GAME>();
  private gameRoom: Map<number, string> = new Map<number, string>();
  private invitations: Map<string, { hostID: number; guestID: number }> =
    new Map<string, { hostID: number; guestID: number }>();

  // eslint-disable-next-line @typescript-eslint/no-empty-function
  constructor(
    private readonly socketService: SocketService,
    private readonly usersService: AppusersService,
    private readonly gamesService: GamesService,
    private readonly roomService: RoomsService,
    private readonly chatService: ChatService,
  ) {}

  setGameService(logger: Logger, wss: Server) {
    this.logger = logger;
    this.wss = wss;
  }

  GetGameRoom(client: Socket): string | false {
    const clientID: number | false =
      this.socketService.findClientIDbySocket(client);
    if (clientID === false) return false;
    return this.gameRoom.get(clientID);
  }

  DelFromGameRoom(client: Socket) {
    const clientID: number | false =
      this.socketService.findClientIDbySocket(client);
    if (clientID === false) return;
    const crntGame: string | false = this.GetGameRoom(client);
    if (crntGame !== false) {
      client.leave(crntGame);
      this.gameRoom.delete(clientID);
    }
  }

  SetInGameRoom(client: Socket, gameUUID: string) {
    const clientID: number | false =
      this.socketService.findClientIDbySocket(client);
    if (clientID === false) return;
    this.DelFromGameRoom(client);
    client.join(gameUUID);
    this.gameRoom.set(clientID, gameUUID);
  }

  getGamesList(client: Socket) {
    const gamesInfos: Array<GameInfo> = new Array<GameInfo>();
    for (const [key, value] of this.games.entries())
      gamesInfos.push(value.getInfos());
    // console.log(gamesInfos);
    this.wss.to(client.id).emit('gamesInfos', gamesInfos);
  }

  clientInGame(client: Socket | number): ClientInGame {
    const clientID: CrntClient =
      typeof client === 'number'
        ? client
        : this.socketService.findClientIDbySocket(client);
    if (clientID !== false) {
      // eslint-disable-next-line @typescript-eslint/no-unused-vars
      for (const [key, value] of this.games.entries())
        if (value.playerOneID === clientID || value.playerTwoID === clientID)
          return {
            ID: clientID,
            game: value,
            player: value.playerOneID === clientID ? 1 : 2,
          };
    }
    return false;
  }

  freeGames(client: Socket) {
    this.games.clear();
    this.getGamesList(client);
    // this.logger.log('free map game OK');
  }

  pressKey(client: Socket, data: { e: string }) {
    const _client: ClientInGame = this.clientInGame(client);
    if (_client !== false) {
      if (_client.player === 1)
        _client.game.court.leftController?.pressKey(data.e);
      else if (_client.player === 2)
        _client.game.court.rightController?.pressKey(data.e);
    }
  }

  realeaseKey(client: Socket, data: { e: string }) {
    const _client: ClientInGame = this.clientInGame(client);
    if (_client !== false) {
      if (_client.player === 1)
        _client.game.court.leftController?.realeaseKey(data.e);
      else if (_client.player === 2)
        _client.game.court.rightController?.realeaseKey(data.e);
    }
  }

  isColor(color: number): string | false {
    const colors: string[] = [
      'aqua',
      'fuchsia',
      'lime',
      'olive',
      'silver',
      'yellow',
      'black',
      'gray',
      'maroon',
      'purple',
      'teal',
      'blue',
      'green',
      'navy',
      'red',
      'white',
    ];
    return colors[color - 1] === undefined ? false : colors[color - 1];
  }

  checkCustomGame(
    client: Socket,
    formular: AskedFormular,
    startButton: boolean,
  ): boolean {
    // console.log('formular test');
    const scoreColor: string | false = this.isColor(formular.scoreColor);
    const boardColor: string | false = this.isColor(formular.boardColor);
    const wallColor: string | false = this.isColor(formular.wallColor);
    const player1: string | false = this.isColor(formular.player1);
    const player2: string | false = this.isColor(formular.player2);
    const ballColor: string | false = this.isColor(formular.ballColor);
    const ballShape: string | false =
      formular.ballShape === 'true' || formular.ballShape === 'false'
        ? formular.ballShape
        : false;
    //const special: boolean =
    //  scoreColor === 'black' &&
    //  boardColor === 'black' &&
    //  wallColor === 'lime' &&
    //  player1 === 'lime' &&
    //  player1 === 'lime' &&
    //  player2 === 'lime' &&
    //  ballColor === 'lime' &&
    //  ballShape === 'true'
    //    ? true
    //    : false;
    const formularAnswer: FormularAnswer = {
      boardColor: boardColor,
      wallColor: wallColor,
      scoreColor: scoreColor,
      player1: player1,
      player2: player2,
      ballColor: ballColor,
      ballShape: ballShape,
//      special: special,
      startButton: startButton,
    };
    const validity: boolean =
      scoreColor &&
      boardColor &&
      wallColor &&
      player1 &&
      player2 &&
      ballColor &&
      ballShape
        ? true
        : false;
    this.wss
      .to(client.id)
      .emit('GameForm', { formularAnswer: formularAnswer, validity: validity });
    return validity;
  }

  startGame(client: Socket, formular: AskedFormular) {
    const clientID: CrntClient =
      this.socketService.findClientIDbySocket(client);
    const _client: ClientInGame = clientID ? this.clientInGame(client) : false;
    if (
      !(clientID && this.games.get(this.gameRoom.get(clientID)) !== undefined)
    )
      return;
    const game: GAME | undefined = this.games.get(this.gameRoom.get(clientID));
    if (!(this.checkCustomGame(client, formular, game.startButton) && _client))
      return;
    else if (_client.player === 1) _client.game.readyPlayerOne = true;
    else if (_client.player === 2) _client.game.readyPlayerTwo = true;
    if (
      _client.game.readyPlayerOne === true &&
      _client.game.readyPlayerTwo === true
    ) {
      _client.game.startButton = false;
      _client.game.CountDown();
    }
  }

  checkGameValidity(client: Socket, gameUUID: string) {
    const game = this.games.get(gameUUID);
    if (game === undefined) {
      this.wss
        .to(client.id)
        .emit('generalErrorMessage', "this game doesn't exist");
      return false;
    }
    return true;
  }

  GameIssue(client: Socket | null, gameUUID: string | false) {
    if (gameUUID !== false) {
      this.invitations.delete(gameUUID);
      this.games.get(gameUUID as string)?.GameIssue(false, this.games);
    } else if (client !== null) {
      // this.logger.log('Game Issue - client ' + client);
      const player: ClientInGame = this.clientInGame(client);
      // this.logger.log('Game Issue - player ' + player);
      if (player) {
        this.invitations.delete(player.game.gameUUID);
        player.game.GameIssue(player, this.games);
      } else this.DelFromGameRoom(client);
    }
  }

  SetAsSpectator(
    client: Socket,
    clientID: number,
    gameUUID: string,
    errorReason: string,
  ) {
    const game: GAME | undefined = this.games.get(gameUUID);
    if (game.playerOneID === clientID) {
      this.wss
        .to(client.id)
        .emit('generalErrorMessage', "you can't spectate your own game");
      return;
    }
    this.GameIssue(client, false);
    this.SetInGameRoom(client, gameUUID);
    this.wss.to(client.id).emit('joinAs', {
      gameUUID: gameUUID,
      errorReason: errorReason,
    });
  }

  async SetPlayerInDefinedGame(
    client: Socket,
    clientID: number,
    gameUUID: string,
  ) {
    const game: GAME | undefined = this.games.get(gameUUID);
    if (game !== undefined) {
      if (game.playerOneID === clientID) {
        this.wss
          .to(client.id)
          .emit('generalErrorMessage', "you can't challenge yourself");
        return;
      }
      // console.log(
      //   'player 2 clientID: ' + clientID + ' vs player1ID: ' + game.playerOneID,
      // );
      game.setPlayerTwo(
        client,
        clientID,
        (await this.usersService.findOneByID(clientID)).pseudo,
      );
      this.invitations.delete(gameUUID);
    }
  }

  async SetPlayerInUndefinedGame(
    client: Socket,
    clientID: number,
    gameType: GameType,
  ) {
    this.GameIssue(client, false);
    for (const [key, value] of this.games.entries()) {
      if (
        value.status === GameStatus.MatchMaking &&
        value.rules.gameType === gameType
      ) {
        // console.log('Found Game for player TWO');
        value.setPlayerTwo(
          client,
          clientID,
          (await this.usersService.findOneByID(clientID)).pseudo,
        );
        return;
      }
    }
    const newGame: GAME = new GAME(
      client,
      this,
      this.games,
      this.gamesService,
      this.wss,
      clientID,
      (await this.usersService.findOneByID(clientID)).pseudo,
      new GameRules(gameType),
    );
  }

  async SetAsPlayer(
    client: Socket,
    clientID: number,
    gameUUID: string | undefined,
    gameType: undefined | GameType,
  ) {
    if (gameUUID !== undefined && gameUUID !== '')
      this.SetPlayerInDefinedGame(client, clientID, gameUUID);
    else
      this.SetPlayerInUndefinedGame(
        client,
        clientID,
        gameType !== GameType.ranked ? GameType.unranked : gameType,
      );
  }

  playAs(
    client: Socket,
    beLike: BeLike,
    gameUUID: string | undefined,
    gameType: undefined | GameType,
  ) {
    const clientID: CrntClient =
      this.socketService.findClientIDbySocket(client);
    if (clientID === false) return;
    let emitEvent = '';
    if (gameUUID !== undefined && gameUUID !== '') {
      if (this.checkGameValidity(client, gameUUID) === false) return;
      // console.log('SetAs - gameUUID ' + gameUUID);
      const game: GAME = this.games.get(gameUUID);
      const invited: undefined | InvitType = this.invitations.get(gameUUID);
      if (invited !== undefined && invited.guestID !== clientID) {
        beLike = BeLike.Spectator;
        emitEvent = "You aren't the guest for this game";
      } else if (beLike === BeLike.Player && game.playerTwoID) {
        // console.log('player 2 debug games list  BAD 2');
        beLike = BeLike.Spectator;
        emitEvent = 'Two player already playing';
      }
    }
    if (beLike) {
      this.SetAsPlayer(client, clientID, gameUUID, gameType);
    } else {
      this.SetAsSpectator(client, clientID, gameUUID, emitEvent);
    }
  }

  async AcceptGame(client: Socket, gameUUID: string) {
    const clientID: CrntClient =
      this.socketService.findClientIDbySocket(client);
    if (clientID === false) return;
    const invitGame = this.invitations.get(gameUUID);
    let beLike: BeLike = BeLike.Player;
    let emitEvent = '';
    if (invitGame !== undefined && invitGame.guestID !== clientID) {
      beLike = BeLike.Spectator;
      emitEvent = "You aren't the guest for this game";
    }
    if (beLike) {
      const game: GAME | undefined = this.games.get(gameUUID);
      if (game !== undefined && game.playerOneID !== clientID) {
        // console.log(
        //   'player 2 clientID: ' +
        //     clientID +
        //     ' vs player1ID: ' +
        //     game.playerOneID,
        // );
        game.setPlayerTwo(
          client,
          clientID,
          (await this.usersService.findOneByID(clientID)).pseudo,
        );
        this.invitations.delete(gameUUID);
      }
    } else {
      this.SetAsSpectator(client, clientID, gameUUID, emitEvent);
    }
  }

  async InvitGame(client: Socket, guestID: number, gameType: GameType) {
    const clientID: CrntClient =
      this.socketService.findClientIDbySocket(client);
    if (clientID === false) return;
    if (clientID === guestID) {
      this.wss
        .to(client.id)
        .emit('generalErrorMessage', "you can't challenge yourself");
      return;
    }
    // console.log(
    //   'InvitGame - clientID: ' +
    //     clientID +
    //     ' - guestID: ' +
    //     guestID +
    //     ' - gametype: ' +
    //     gameType,
    // );
    let channelDM = await this.roomService.getOneDM(clientID, guestID);
    if (channelDM === undefined) {
      this.wss
        .to(client.id)
        .emit('generalErrorMessage', "you can't DM yourself");
      return;
    } else if (channelDM === null) {
      channelDM = await this.roomService.createDM(clientID, guestID, true);
      this.chatService.addChannel(channelDM.id, channelDM.name);
      this.wss.emit('rooms-updated');
    }
    // console.log('InvitGame - channelDM: ' + channelDM);

    this.GameIssue(client, false);
    const newGame: GAME = new GAME(
      client,
      this,
      this.games,
      this.gamesService,
      this.wss,
      clientID,
      (await this.usersService.findOneByID(clientID)).pseudo,
      new GameRules(gameType),
    );
    this.invitations.set(newGame.gameUUID, {
      hostID: clientID,
      guestID: guestID,
    });
    const invitGame: string =
      '\\invitation-' + clientID + '-' + gameType + '-' + newGame.gameUUID;
    await this.roomService.addMessageToRoom(channelDM.id, clientID, invitGame);
    const channelUUID: false | string = this.chatService.getRoomById(
      channelDM.id,
    );
    if (channelUUID) {
      // console.log('InvitGame - channelUUID' + channelUUID);
      this.wss
        .to(channelUUID)
        .emit('message-received', { id: clientID, message: invitGame });
    }
  }
}
