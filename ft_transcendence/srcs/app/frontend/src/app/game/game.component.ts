import { Component, OnDestroy, OnInit } from '@angular/core';
import { WebSocketsService } from '../shared/web-sockets.service';

type AskedFormular = {
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

export interface GAME_SETTINGS {
  //special: boolean;
  boardColor: string;
  wallColor: string;
  wallSize: number;
  courtMarginX: number;
  courtMarginY: number;
  targetFps: number;

  playerOneColor: string;
  playerTwoColor: string;

  winScore: number;

  smallFount: string;
  largeFount: string;
  scoreColor: string;

  hitBatSound: string;
  hitWallSound: string;
  winPointSound: string;

  paddleWidth: number;
  paddleHeight: number;
  ballRadius: number;
  ballColor: string;
  ballShape: boolean;
}

export interface FORMAT {
  widthBoardRate: number;
  heightBoardRate: number;
}

@Component({
  selector: 'app-game',
  templateUrl: './game.component.html',
  styleUrls: ['./game.component.css'],
})
export class GameComponent implements OnInit, OnDestroy {
  errorForm: boolean;
  errorScoreColor: boolean;
  errorBoardColor: boolean;
  errorWallColor: boolean;
  errorPlayer1: boolean;
  errorPlayer2: boolean;
  errorBallColor: boolean;
  errorBallShape: boolean;

  constructor(private wss: WebSocketsService) {
    this.errorForm = false;
    this.errorScoreColor = false;
    this.errorBoardColor = false;
    this.errorWallColor = false;
    this.errorPlayer1 = false;
    this.errorPlayer2 = false;
    this.errorBallColor = false;
    this.errorBallShape = false;
  }

  formularError(data: FormularAnswer) {
    this.errorScoreColor = !data.scoreColor ? true : false;
    this.errorBoardColor = !data.boardColor ? true : false;
    this.errorWallColor = !data.wallColor ? true : false;
    this.errorPlayer1 = !data.player1 ? true : false;
    this.errorPlayer2 = !data.player2 ? true : false;
    this.errorBallColor = !data.ballColor ? true : false;
    this.errorBallShape = !data.ballShape ? true : false;
  }

  ngOnInit(): void {
    this.wss.endGameListener();
    this.wss.on(
      'GameForm',
      (data: { formularAnswer: FormularAnswer; validity: boolean }) => {
        const form: FormularAnswer = data.formularAnswer;
        // console.log('formular test');
        this.errorForm = data.validity ? false : true;
        if (this.errorForm) this.formularError(form);
        else {
          // console.log('formular test success');
          this.wss.removeListener('GameForm');
          const gameBoard: HTMLCanvasElement = document.getElementsByClassName(
            'board',
          )[0] as HTMLCanvasElement;
          const format: { widthBoardRate: number; heightBoardRate: number } = {
            widthBoardRate: 17,
            heightBoardRate: 14,
          };
          const gameSettings: GAME_SETTINGS = {
            scoreColor: form.scoreColor as string,
            smallFount: gameBoard.width / 24 + 'px Arial',
            largeFount: gameBoard.width / 16 + 'px Arial',

            boardColor: form.boardColor as string,
            wallColor: form.wallColor as string,
            wallSize: (gameBoard.height * 2) / format.heightBoardRate,
            courtMarginX: (gameBoard.width * 1) / format.heightBoardRate,
            courtMarginY: (gameBoard.height * 0.5) / format.heightBoardRate,
            targetFps: 60,

            playerOneColor: form.player1 as string,
            playerTwoColor: form.player2 as string,

            winScore: 7,

            hitBatSound: '/assets/apingpongbat.ogg',
            hitWallSound: '/assets/pingpongboard.ogg',
            winPointSound: '/assets/Win sound.wav',

            paddleWidth: (gameBoard.width * 0.5) / format.widthBoardRate,
            paddleHeight:
              (gameBoard.height -
                (gameBoard.height * 5) / format.heightBoardRate) /
              4,
            ballRadius: 3,
            ballColor: form.ballColor as string,
            ballShape: form.ballShape === 'true' ? true : false,
           // special: form.special,
          };
          const settings: HTMLDivElement = document.getElementsByClassName(
            'settings',
          )[0] as HTMLDivElement;
          settings?.parentNode?.removeChild(settings);
          const start: HTMLButtonElement = document.getElementsByClassName(
            'start',
          )[0] as HTMLButtonElement;
          start.innerHTML = 'waiting...';
          this.wss.gameListener(
            gameBoard,
            format,
            gameSettings,
            form.startButton,
          );
        }
      },
    );
  }

  readyTo(): void {
    const formularAsked: AskedFormular = {
      scoreColor: +(
        document.getElementsByClassName('scoreColor')[0] as HTMLSelectElement
      ).value,
      boardColor: +(
        document.getElementsByClassName('boardColor')[0] as HTMLSelectElement
      ).value,
      wallColor: +(
        document.getElementsByClassName('wallColor')[0] as HTMLSelectElement
      ).value,
      player1: +(
        document.getElementsByClassName('player1')[0] as HTMLSelectElement
      ).value,
      player2: +(
        document.getElementsByClassName('player2')[0] as HTMLSelectElement
      ).value,
      ballColor: +(
        document.getElementsByClassName('ballColor')[0] as HTMLSelectElement
      ).value,
      ballShape: (
        document.getElementsByClassName('ballShape')[0] as HTMLSelectElement
      ).value,
    };
    this.wss.emit('StartGame', formularAsked);
  }

  ngOnDestroy(): void {
    this.wss.emit('abandonGame');
    this.wss.gameDeafener();
  }
}
