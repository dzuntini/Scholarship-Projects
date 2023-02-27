import { Server, Socket } from 'socket.io';
import { CreateGameDto } from 'src/games/dto/create-game.dto';
import { GamesService } from 'src/games/games.service';
import { ClientInGame, GameService } from './game.service';
import {v4 as uuidv4} from 'uuid';

export enum GameType {
  unranked = 0,
  ranked = 1,
}

export enum GameStatus {
  MatchMaking = 1,
  WaitingPlayers = 2,
  Playing = 3,
  Finished = 4,
  Processed = 5,
}

export type GameInfo = {
  UUID: string;
  gameType: GameType;
  status: string;
  p1: { pseudo: string; score: number };
  p2: { pseudo: string; score: number };
};

export class GameRules {
  width: number;
  height: number;
  widthBoardRate: number;
  heightBoardRate: number;
  targetFps: number;

  wallSize: number;
  courtMarginX: number;
  courtMarginY: number;

  gameType: GameType;
  winScore: number;

  paddleWidth: number;
  paddleHeight: number;
  ballRadius: number;

  constructor(gameType: GameType) {
    this.width = 1700;
    this.height = 1400;
    this.widthBoardRate = 17;
    this.heightBoardRate = 14;
    this.targetFps = 60;

    this.wallSize = (this.height * 2) / this.heightBoardRate;
    this.courtMarginX = (this.width * 1) / this.heightBoardRate;
    this.courtMarginY = (this.height * 0.5) / this.heightBoardRate;
    this.targetFps = 60;

    this.gameType = gameType;
    this.winScore = 5;

    this.paddleWidth = (this.width * 0.5) / this.widthBoardRate;
    this.paddleHeight =
      (this.height - (this.height * 5) / this.heightBoardRate) / 4;
    this.ballRadius = 3;
  }
}

class hitBox {
  x: number;
  y: number;
  width: number;
  height: number;
  middle: number;

  constructor(x: number, y: number, width: number, height: number) {
    this.x = x;
    this.y = y;
    this.width = width;
    this.height = height;
    this.middle = y + height / 2;
  }

  get left() {
    return this.x;
  }

  get right() {
    return this.x + this.width;
  }

  get top() {
    return this.y;
  }

  get bottom() {
    return this.y + this.height;
  }

  overlaps(other: hitBox) {
    return (
      other.left <= this.right &&
      this.left <= other.right &&
      other.top <= this.bottom &&
      this.top <= other.bottom
    );
  }

  contain(x: number, y: number) {
    return this.left < x && this.right > x && this.top < y && this.bottom > y;
  }
}

class Ball {
  gameRules: GameRules;
  _court: Court;

  posX: number;
  posY: number;
  radius: number;

  offsetY: number;
  vector: { x: number; y: number };
  _speed: number;

  static get minSpeed() {
    return 600;
  }

  static get maxSpeed() {
    return 1500;
  }

  static get acceleration() {
    return 8;
  }

  constructor(posX: number, posY: number, gameRules: GameRules, court: Court) {
    this.gameRules = gameRules;
    this._court = court;

    this.posX = posX;
    this.posY = posY;
    this.offsetY = 0;
    this.radius = gameRules.ballRadius;

    this.vector = { x: 0, y: 0 };
    this._speed = Ball.minSpeed;
  }

  set speed(val) {
    if (val < Ball.minSpeed) val = Ball.minSpeed;
    else if (val > Ball.maxSpeed) val = Ball.maxSpeed;
    this._speed = val;
  }

  get speed() {
    return this._speed;
  }

  get normalizedSpeed() {
    return (this._speed - Ball.minSpeed) / (Ball.maxSpeed - Ball.minSpeed);
  }

  get collisionBox() {
    return new hitBox(
      this.posX - this.radius,
      this.posY - this.radius,
      this.gameRules.ballRadius * 2,
      this.gameRules.ballRadius * 2,
    );
  }

  get velocity() {
    return this.vector;
  }

  set velocity(val) {
    this.vector = val;
  }

  changeAngle(collisionBox: hitBox) {
    this.velocity.x = -this.velocity.x;
    const impact: number = this.posY - collisionBox.top;
    const ratePaddle: number = impact / collisionBox.height;

    if (ratePaddle < 0.1) this.velocity.y = -1;
    else if (ratePaddle < 0.2) this.velocity.y = -0.75;
    else if (ratePaddle < 0.3) this.velocity.y = -0.5;
    else if (ratePaddle < 0.4) this.velocity.y = -0.25;
    else if (ratePaddle > 0.9) this.velocity.y = 1;
    else if (ratePaddle > 0.8) this.velocity.y = 0.75;
    else if (ratePaddle > 0.7) this.velocity.y = 0.5;
    else if (ratePaddle > 0.6) this.velocity.y = 0.25;
    else this.velocity.y = 0;
  }

  update(timeLaps: number) {
    this.posY += this.velocity.y * this.speed * timeLaps;

    if (this.posY - this.radius < this._court.bounds.upper) {
      this.posY = this._court.bounds.upper + this.radius;
      this.velocity.y *= -1;
    } else if (this.posY + this.radius > this._court.bounds.lower) {
      this.posY = this._court.bounds.lower - this.radius;
      this.velocity.y *= -1;
    }

    const leftCollisionBox = this._court.leftPaddle.collisionBox;
    const rightCollisionBox = this._court.rightPaddle.collisionBox;

    if (this.collisionBox.overlaps(leftCollisionBox)) {
      this.posX = this._court.leftPaddle.collisionBox.right + this.radius;
      this.changeAngle(leftCollisionBox);
    } else if (this.collisionBox.overlaps(rightCollisionBox)) {
      this.posX = this._court.rightPaddle.collisionBox.left - this.radius;
      this.changeAngle(rightCollisionBox);
    }

    this.posX += Math.sign(this.velocity.x) * this.speed * timeLaps;
    if (this.posX < this._court.bounds.left) {
      this._court.scorePoint(this._court.p2);
    } else if (this.posX > this._court.bounds.right) {
      this._court.scorePoint(this._court.p1);
    }
    this.speed += Ball.acceleration * timeLaps;
  }
}

class ScoreBoard {
  p1: number;
  p1Score: number;
  p2: number;
  p2Score: number;
  round: number;
  gameRules: GameRules;

  constructor(gameRules: GameRules, p1: number, p2: number) {
    this.p1Score = 0;
    this.p2Score = 0;
    this.round = 1;
    this.gameRules = gameRules;
    this.p1 = p1;
    this.p2 = p2;
  }

  get winner() {
    if (this.p1Score === this.gameRules.winScore) {
      return this.p1;
    } else if (this.p2Score === this.gameRules.winScore) {
      return this.p2;
    }
    return 0;
  }

  reset() {
    this.p1Score = 0;
    this.p2Score = 0;
    this.round = 1;
  }
}

export class Paddle {
  posX: number;
  posY: number;
  width: number;
  height: number;
  playerIndex: number;
  _court: Court;
  _startPosX: number;
  _startPosY: number;

  constructor(
    posX: number,
    posY: number,
    width: number,
    height: number,
    playerIndex: number,
    court: Court,
  ) {
    this.posX = posX;
    this.posY = posY;
    this.width = width;
    this.height = height;
    this.playerIndex = playerIndex;
    this._startPosX = posX;
    this._startPosY = posY;
    this._court = court;
  }

  static get speed() {
    return 150;
  }

  get collisionBox() {
    return new hitBox(this.posX, this.posY, this.width, this.height);
  }

  moveUp(timeLaps: number) {
    this.posY -= (this._court.ball.speed - Paddle.speed) * timeLaps;
    if (this.posY < this._court.bounds.upper)
      this.posY = this._court.bounds.upper;
  }

  moveDown(timeLaps: number) {
    this.posY += (this._court.ball.speed - Paddle.speed) * timeLaps;
    if (this.posY + this.height > this._court.bounds.lower)
      this.posY = this._court.bounds.lower - this.height;
  }

  reset() {
    this.posX = this._startPosX;
    this.posY = this._startPosY;
  }
}

export class PaddleController {
  paddle: Paddle;
  isUpKeyPressed: boolean;
  isDownKeyPressed: boolean;

  constructor(paddle: Paddle) {
    this.paddle = paddle;
    this.isUpKeyPressed = false;
    this.isDownKeyPressed = false;
  }

  pressKey(e: string) {
    if (e === 'ArrowUp' || e === 'w' || e === 'z') this.isUpKeyPressed = true;
    else if (e === 'ArrowDown' || e === 's') this.isDownKeyPressed = true;
  }

  realeaseKey(e: string) {
    if (e === 'ArrowUp' || e === 'w' || e === 'z') this.isUpKeyPressed = false;
    else if (e === 'ArrowDown' || e === 's') this.isDownKeyPressed = false;
  }

  update(timeLaps: number) {
    if (!(this.isUpKeyPressed && this.isDownKeyPressed)) {
      this.isDownKeyPressed
        ? this.paddle.moveDown(timeLaps)
        : this.isUpKeyPressed
        ? this.paddle.moveUp(timeLaps)
        : 0;
    }
  }
}

class Court {
  leftPaddle: Paddle;
  leftController: PaddleController;

  rightPaddle: Paddle;
  rightController: PaddleController;

  ball: Ball;
  gameRules: GameRules;
  scoreBoard: ScoreBoard;
  p1: number;
  p2: number;
  p1Pseudo: string;
  p2Pseudo: string;

  wss: Server;
  constructor(
    wss: Server,
    gameRules: GameRules,
    p1: { id: number; pseudo: string },
  ) {
    this.gameRules = gameRules;
    this.leftPaddle = new Paddle(
      0,
      gameRules.height / 2 - gameRules.paddleHeight / 2,
      gameRules.paddleWidth,
      gameRules.paddleHeight,
      p1.id,
      this,
    );
    this.p1 = p1.id;
    this.p1Pseudo = p1.pseudo;
    this.wss = wss;
  }

  get bounds() {
    return {
      upper: this.gameRules.courtMarginY + this.gameRules.wallSize,
      lower:
        this.gameRules.height -
        (this.gameRules.courtMarginY + this.gameRules.wallSize),
      left: 0,
      right: this.gameRules.width,
    };
  }

  update(timeLaps: number) {
    if (!this.scoreBoard.winner) {
      this.leftController?.update(timeLaps);
      this.rightController?.update(timeLaps);
      this.ball?.update(timeLaps);
    }
  }

  startMatch() {
    this._spawnBall();
    this.scoreBoard.reset();
    this.leftPaddle.reset();
    this.rightPaddle.reset();
  }

  _spawnBall() {
    this.ball.velocity = {
      x: Math.random() > 0.5 ? 1 : -1,
      y: 0,
    };
    this.ball.posX = this.gameRules.width / 2;
    this.ball.posY = this.gameRules.height / 2;
    this.ball.speed = Ball.minSpeed;
  }

  scorePoint(playerIndex: number) {
    playerIndex === this.p1
      ? ++this.scoreBoard.p1Score
      : ++this.scoreBoard.p2Score;

    const winner: number = this.scoreBoard.winner;
    this.wss.emit('pointEvent', {
      round: winner ? this.scoreBoard.round : this.scoreBoard.round++,
      ballX: this.ball.posX,
      ballY: this.ball.posY,
      player1: { pseudo: this.p1Pseudo, score: this.scoreBoard.p1Score },
      player2: { pseudo: this.p2Pseudo, score: this.scoreBoard.p2Score },
    });
    // console.log(this.scoreBoard.round);
    if (!winner) this._spawnBall();
  }
}

export class GAME {
  gamesService: GamesService;
  gameService: GameService;
  games: Map<string, GAME>;
  gameRoom: Map<number, string>;
  gameUUID: string;

  playerOneID: number;
  playerTwoID: number;
  playerOnePseudo: string;
  playerTwoPseudo: string;

  court: Court;
  rules: GameRules;
  wss: Server;
  status: GameStatus;

  readyPlayerOne: boolean;
  readyPlayerTwo: boolean;
  countDown: number;

  startButton: boolean;
  timer: NodeJS.Timer;
  frame: NodeJS.Timer;

  constructor(
    client: Socket,
    gameService: GameService,
    games: Map<string, GAME>,
    gamesService: GamesService,
    wss: Server,
    clientID: number,
    clientPseudo: string,
    gameRules: GameRules,
  ) {
    this.gameService = gameService;
    this.gamesService = gamesService;
    this.gameUUID = uuidv4();
    this.playerOneID = clientID;
    this.playerOnePseudo = clientPseudo;
    this.playerTwoID = 0;
    this.playerTwoPseudo = '';

    this.readyPlayerOne = false;
    this.readyPlayerTwo = false;
    this.countDown = 4;
    this.startButton = true;

    this.status = GameStatus.MatchMaking;
    this.rules = gameRules;
    this.wss = wss;
    this.court = new Court(this.wss, this.rules, {
      id: this.playerOneID,
      pseudo: this.playerOnePseudo,
    });
    games.set(this.gameUUID, this);
    this.gameService.SetInGameRoom(client, this.gameUUID);
    this.wss.emit('addGame', this.getInfos());
    // console.log('ClientID: ' + clientID + ' setting in ' + this.gameUUID);
  }

  statusToString(gameStatus: GameStatus): string {
    switch (gameStatus) {
      case GameStatus.MatchMaking:
        return 'matchmaking';
      case GameStatus.WaitingPlayers:
        return 'waiting for ready players';
      case GameStatus.Playing:
        return 'playing';
      default:
        return 'completed';
    }
  }

  getInfos(): GameInfo {
    return {
      UUID: this.gameUUID,
      gameType: this.rules.gameType,
      status: this.statusToString(this.status),
      p1: {
        pseudo: this.playerOnePseudo,
        score: this.court.scoreBoard ? this.court.scoreBoard.p1Score : 0,
      },
      p2: {
        pseudo:
          this.status === GameStatus.MatchMaking
            ? 'waiting...'
            : this.playerTwoPseudo,
        score: this.court.scoreBoard ? this.court.scoreBoard.p2Score : 0,
      },
    };
  }

  _update(timeLaps: number) {
    this.court.update(timeLaps);
  }

  GetIntervalLength(): number {
    return 1.0 / this.rules.targetFps;
  }

  async CloseGame(
    gameStatus: GameStatus,
    games: Map<string, GAME>,
    _score1: number,
    _score2: number,
  ) {
    // console.log('close game enter game status: ' + gameStatus);
    type endInfos = {
      type: string;
      winner: string | null;
      score: null | {
        p1: string;
        p2: string;
      };
    };
    const end: endInfos = {
      type: '',
      winner: null,
      score: null,
    };
    if (gameStatus < GameStatus.Playing) end.type = 'game canceled';
    else if (gameStatus === GameStatus.Playing) {
      end.type =
        (_score1 === -42 ? this.playerOnePseudo : this.playerTwoPseudo) +
        ' resigns';
      end.score = null;
    } else {
      end.type = 'game compleated';
      end.score = {
        p1: this.playerOnePseudo + ' : ' + _score1,
        p2: this.playerTwoPseudo + ' : ' + _score2,
      };
    }
    if (gameStatus > GameStatus.WaitingPlayers)
      end.winner =
        _score1 > _score2 ? this.playerOnePseudo : this.playerTwoPseudo;
    else end.winner = null;

    if (gameStatus > GameStatus.WaitingPlayers) {
      const gameDTO: CreateGameDto = {
        ranked: this.rules.gameType === GameType.ranked ? true : false,
        p1_score: _score1,
        p2_score: _score2,
      };
      await this.gamesService.create(
        gameDTO,
        this.playerOneID,
        this.playerTwoID,
        gameStatus,
      );
    }
    this.wss.to(this.gameUUID).emit('endGame', end);
    const sockets: any = await this.wss.to(this.gameUUID).fetchSockets();
    for (const socket of sockets) this.gameService.DelFromGameRoom(socket);
    // console.log('Deleted Game ' + this.gameUUID);
    games.delete(this.gameUUID);
    this.wss.emit('rmvGame', this.gameUUID);
  }

  GameIssue(_client: ClientInGame, games: Map<string, GAME>) {
    // console.log('before game issue clear interval');
    clearInterval(this.frame);
    // console.log('after game issue clear interval');
    const gameStatus: GameStatus = this.status;
    if (gameStatus !== GameStatus.Processed) {
      this.status = GameStatus.Processed;
      let _score1: number;
      let _score2: number;
      if (this.status > GameStatus.WaitingPlayers) {
        _score1 =
          _client !== false &&
          _client.player === 1 &&
          gameStatus === GameStatus.Playing
            ? -42
            : this.court.scoreBoard
            ? this.court.scoreBoard.p1Score
            : 0;
        _score2 =
          _client !== false &&
          _client.player === 2 &&
          gameStatus === GameStatus.Playing
            ? -42
            : this.court.scoreBoard
            ? this.court.scoreBoard.p2Score
            : 0;
      }
      this.CloseGame(gameStatus, games, _score1, _score2);
    }
  }

  DrawBack() {
    // console.log('DrawBack called');
    let previousUpdateTime: number = Date.now();

    const drawBack = () => {
      if (this.status !== GameStatus.Processed) {
        if (!this.court.scoreBoard.winner) {
          const updateTime = Date.now();
          const timeLaps = (updateTime - previousUpdateTime) / 1000.0;
          this._update(timeLaps);
          previousUpdateTime = updateTime;
          this.wss.emit('cycleEvent', {
            round: this.court.scoreBoard.round,
            ballX: this.court.ball.posX / 1700,
            ballY: this.court.ball.posY / 1400,
            player1: {
              pseudo: this.playerOnePseudo,
              paddleY: this.court.leftPaddle.posY / 1400,
              score: this.court.scoreBoard.p1Score,
            },
            player2: {
              pseudo: this.playerTwoPseudo,
              paddleY: this.court.rightPaddle.posY / 1400,
              score: this.court.scoreBoard.p2Score,
            },
          });
        } else {
          this.status = GameStatus.Finished;
          this.gameService.GameIssue(null, this.gameUUID);
        }
      }
    };

    this.frame = setInterval(drawBack, this.GetIntervalLength() * 1000.0);
    clearInterval(this.timer);
  }

  setPlayerTwo(client: Socket, clientID: number, clientPseudo: string) {
    // console.log('player 2 debug games list  4');
    this.gameService.GameIssue(client, false);
    this.playerTwoID = clientID;
    this.playerTwoPseudo = clientPseudo;
    this.court.rightPaddle = new Paddle(
      this.rules.paddleWidth +
        (this.rules.width - this.rules.width / this.rules.widthBoardRate),
      this.rules.height / 2 - this.rules.paddleHeight / 2,
      this.rules.paddleWidth,
      this.rules.paddleHeight,
      clientID,
      this.court,
    );
    this.court.p2 = clientID;
    this.court.p2Pseudo = clientPseudo;
    this.status = GameStatus.WaitingPlayers;
    this.gameService.SetInGameRoom(client, this.gameUUID);
    this.wss.emit('get-status-response', {
      id: this.playerOneID,
      status: 2,
    });
    this.wss.emit('get-status-response', {
      id: this.playerTwoID,
      status: 2,
    });
    this.wss
      .to(this.gameUUID)
      .emit('joinAs', { gameUUID: this.gameUUID, errorReason: '' });
    this.wss.emit('chgGame', this.getInfos());
  }

  emitCountDownEvent() {
    this.wss.emit('countDownEvent', {
      countDown: this.countDown,
      ball: {
        posX: this.court?.ball?.posX / 1700,
        posY: this.court?.ball?.posY / 1400,
      },
      player1: { pseudo: this.playerOnePseudo, score: 0 },
      player2: { pseudo: this.playerTwoPseudo, score: 0 },
      paddles: {
        leftY: this.court?.leftPaddle?.posY / 1400,
        rightY: this.court?.rightPaddle?.posY / 1400,
      },
    });
  }

  CountDown() {
    this.status = GameStatus.Playing;
    this.timer = setInterval(() => {
      if (this.countDown === 2) {
        this.court.scoreBoard = new ScoreBoard(
          this.rules,
          this.playerOneID,
          this.playerTwoID,
        );
      } else if (this.countDown === 1) {
        this.court.leftController = new PaddleController(this.court.leftPaddle);
        this.court.rightController = new PaddleController(
          this.court.rightPaddle,
        );
      } else if (this.countDown === -1) {
        this.court.ball = new Ball(
          this.rules.width / 2,
          this.rules.height / 2,
          this.rules,
          this.court,
        );
        this.emitCountDownEvent();
        this.court.startMatch();
        this.DrawBack();
      }
      if (this.countDown !== -1) this.emitCountDownEvent();
      if (this.countDown !== -2) --this.countDown;
    }, 1000);
  }
}
