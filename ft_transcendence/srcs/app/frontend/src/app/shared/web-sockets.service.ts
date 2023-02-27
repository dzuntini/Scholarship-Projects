import { Injectable } from '@angular/core';
import { Socket } from 'ngx-socket-io';
import { Router } from '@angular/router';
import { FORMAT, GAME_SETTINGS } from '../game/game.component';
import { MatDialog } from '@angular/material/dialog';
import { EndGameComponent } from '../end-game/end-game.component';

export type endInfos = {
  type: string;
  winner: string | null;
  score: null | {
    p1: string;
    p2: string;
  };
};

@Injectable({
  providedIn: 'root',
})
export class WebSocketsService {
  constructor(
    private router: Router,
    private socket: Socket,
    private dialog: MatDialog,
  ) {}

  emit(eventName: string, data?: object) {
    // console.log('Emit event for ' + eventName);
    this.socket.emit(eventName, data);
  }

  // eslint-disable-next-line @typescript-eslint/ban-types
  on(eventName: string, func: Function) {
    // console.log('event ' + eventName + ' correctly init');
    this.socket.on(eventName, func);
  }

  generalListener() {
    this.socket.on('valided connection', (data: object) => {
      // console.log(data);
    });
  }

  removeListener(listener: string) {
    this.socket.removeListener(listener);
  }

  forceDisconnectListener() {
    this.socket.on('forceDisconnect', () => {
      window.localStorage.removeItem('accessToken');
      this.router.navigate(['Login']);
    });
  }

  gameDeafener() {
    this.socket.removeListener('endGame');
    this.socket.removeListener('pointEvent');
    this.socket.removeListener('countDownEvent');
    this.socket.removeListener('cycleEvent');
    this.socket.removeListener('gameEvent');
    this.socket.removeListener('winnerEvent');
  }

  scoreDraw(
    gameBoard: HTMLCanvasElement,
    format: FORMAT,
    gameSettings: GAME_SETTINGS,
    round: number,
    player1: { pseudo: string; score: number },
    player2: { pseudo: string; score: number },
  ) {
    const ctx: CanvasRenderingContext2D | null = gameBoard.getContext('2d');
    if (ctx) {
      ctx.font = gameSettings.smallFount;
      ctx.fillStyle = gameSettings.scoreColor;

      const startScore =
        player2.score / 10 ? gameBoard.width - 98 : gameBoard.width - 90;
      ctx.fillText(
        'Round: ' + round,
        gameBoard.width / 2 - 30,
        (gameBoard.height / format.heightBoardRate) * 1.85,
      );
      ctx.fillText(
        player1.pseudo + ' | ' + player1.score,
        8,
        (gameBoard.height / format.heightBoardRate) * 12.85,
      );
      ctx.fillText(
        player2.pseudo + ' | ' + player2.score,
        startScore,
        (gameBoard.height / format.heightBoardRate) * 12.85,
      );
    }
  }

  ballDraw(
    gameBoard: HTMLCanvasElement,
    ballX: number,
    ballY: number,
    gameSettings: GAME_SETTINGS,
  ) {
    // console.log('BallX: ' + ballX, 'BallY: ' + ballY);
    const ctx = gameBoard.getContext('2d');
    if (ctx) {
	  ctx.fillStyle = gameSettings.ballColor;
      ctx.beginPath();
      gameSettings.ballShape === false
        ? ctx.arc(
            ballX * gameBoard.width,
            ballY * gameBoard.height,
            gameSettings.ballRadius,
            0,
            Math.PI * 2,
            false,
          )
        : ctx.fillRect(
            ballX * gameBoard.width - gameSettings.ballRadius,
            ballY * gameBoard.height - gameSettings.ballRadius,
            gameSettings.ballRadius * 2,
            gameSettings.ballRadius * 2,
          );
      ctx.fill();
    }
  }

  paddlesDraw(
    gameBoard: HTMLCanvasElement,
    leftPaddleY: number,
    rightPaddleY: number,
    gameSettings: GAME_SETTINGS,
  ) {
    const ctx = gameBoard.getContext('2d');
    if (ctx) {
      // console.log(
      //  'left paddle Y: ' + leftPaddleY,
      //  'right paddle y: ' + rightPaddleY,
      // );
      ctx.fillStyle = gameSettings.playerOneColor;
      ctx.fillRect(
        0,
        leftPaddleY * gameBoard.height,
        gameSettings.paddleWidth,
        gameSettings.paddleHeight,
      );
      ctx.fillStyle = gameSettings.playerTwoColor;
      ctx.fillRect(
        gameBoard.width - gameSettings.paddleWidth,
        rightPaddleY * gameBoard.height,
        gameSettings.paddleWidth,
        gameSettings.paddleHeight,
      );
    }
  }

  courtDraw(gameBoard: HTMLCanvasElement, gameSettings: GAME_SETTINGS) {
    const ctx: CanvasRenderingContext2D | null = gameBoard.getContext('2d');
    if (ctx) {
      ctx.fillStyle = gameSettings.wallColor;
      ctx.fillRect(
        0,
        gameSettings.courtMarginY,
        gameBoard.width,
        gameSettings.wallSize,
      );
      ctx.fillRect(
        0,
        gameBoard.height - gameSettings.courtMarginY - gameSettings.wallSize,
        gameBoard.width,
        gameSettings.wallSize,
      );
    }
  }

  drawBoardgame(gameBoard: HTMLCanvasElement, gameSettings: GAME_SETTINGS) {
    //if (!gameSettings.special)
    gameBoard.style.backgroundColor = gameSettings.boardColor;
    const ctx: CanvasRenderingContext2D | null = gameBoard.getContext('2d');
    ctx?.clearRect(0, 0, gameBoard.width, gameBoard.height);
  }

  removeStart(gameBoard: HTMLCanvasElement, gameSettings: GAME_SETTINGS) {
    const startButton: HTMLButtonElement = document.getElementsByClassName(
      'start',
    )[0] as HTMLButtonElement;
    startButton.parentNode?.parentNode?.removeChild(startButton.parentNode);
    //if (!gameSettings.special)
    gameBoard.style.backgroundColor = gameSettings.boardColor;
  }

  endGameListener() {
    this.socket.on('endGame', (data: endInfos) => {
      this.gameDeafener();
      const gameBoard: HTMLCanvasElement = document.getElementsByClassName(
        'board',
      )[0] as HTMLCanvasElement;
      const form: HTMLFormElement = document.getElementsByClassName(
        'game-settings',
      )[0] as HTMLFormElement;
      form?.parentElement?.removeChild(form);
      const endGame = this.dialog.open(EndGameComponent, { data });
      endGame.afterClosed().subscribe(() => {
        this.router.navigate(['']);
      });
    });
  }

  gameListener(
    gameBoard: HTMLCanvasElement,
    format: FORMAT,
    gameSettings: GAME_SETTINGS,
    startButton: boolean,
  ) {
    // console.log('start button : ' + startButton);
    if (!startButton) this.removeStart(gameBoard, gameSettings);
    //if (!gameSettings.special)
    gameBoard.style.backgroundColor = gameSettings.boardColor;

    this.socket.on(
      'pointEvent',
      (data: {
        round: number;
        ballX: number;
        ballY: number;
        player1: { pseudo: string; score: number };
        player2: { pseudo: string; score: number };
      }) => {
        this.drawBoardgame(gameBoard, gameSettings);
        this.ballDraw(gameBoard, data.ballX, data.ballY, gameSettings);
        this.courtDraw(gameBoard, gameSettings);
        this.scoreDraw(
          gameBoard,
          format,
          gameSettings,
          data.round,
          data.player1,
          data.player2,
        );
      },
    );

    this.socket.on(
      'countDownEvent',
      (data: {
        countDown: number;
        ball: { posX: number; posY: number };
        player1: { pseudo: string; score: number };
        player2: { pseudo: string; score: number };
        paddles: { leftY: number; rightY: number };
      }) => {
        const startButton: HTMLButtonElement = document.getElementsByClassName(
          'start',
        )[0] as HTMLButtonElement;
        // console.log('countdown is: ' + data.countDown);
        if (data.countDown === 4) {
          startButton.disabled = true;
          startButton.textContent = 'ready!?';
        } else if (data.countDown === 2) {
          this.courtDraw(gameBoard, gameSettings);
          this.scoreDraw(
            gameBoard,
            format,
            gameSettings,
            1,
            data.player1,
            data.player2,
          );
          startButton.textContent = data.countDown.toString();
        } else if (data.countDown === 1) {
          this.paddlesDraw(
            gameBoard,
            data.paddles.leftY,
            data.paddles.rightY,
            gameSettings,
          );
          startButton.textContent = data.countDown.toString();
        } else if (data.countDown === 0) {
          startButton.textContent = 'go!!!';
          document.addEventListener('keydown', (e) => {
            this.socket.emit('pressKey', { e: e.key });
          });
          document.addEventListener('keyup', (e) => {
            this.socket.emit('realeaseKey', { e: e.key });
          });
        } else if (data.countDown === -1) {
          this.removeStart(gameBoard, gameSettings);
          this.ballDraw(
            gameBoard,
            data.ball.posX,
            data.ball.posY,
            gameSettings,
          );
        } else {
          startButton.textContent = data.countDown.toString();
        }
      },
    );

    this.socket.on(
      'cycleEvent',
      (data: {
        round: number;
        ballX: number;
        ballY: number;
        player1: { pseudo: string; paddleY: number; score: number };
        player2: { pseudo: string; paddleY: number; score: number };
      }) => {
        // console.log('cycleEvent trigger');
        this.drawBoardgame(gameBoard, gameSettings);
        this.ballDraw(gameBoard, data.ballX, data.ballY, gameSettings);
        this.courtDraw(gameBoard, gameSettings);
        this.scoreDraw(
          gameBoard,
          format,
          gameSettings,
          data.round,
          { pseudo: data.player1.pseudo, score: data.player1.score },
          { pseudo: data.player2.pseudo, score: data.player2.score },
        );
        this.paddlesDraw(
          gameBoard,
          data.player1.paddleY,
          data.player2.paddleY,
          gameSettings,
        );
      },
    );
  }
}
