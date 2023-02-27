import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { WebSocketsService } from '../shared/web-sockets.service';
import { MatDialog } from '@angular/material/dialog';
import { ErrorJoinGameComponent } from '../error-join-game/error-join-game.component';

export enum BeLike {
  Spectator = 0,
  Player = 1,
}

export enum GameType {
  unranked = 0,
  ranked = 1,
}

export type GameInfo = {
  //	  type: boolean; FOR UNRANKED IMPLEMENTATION
  UUID: string;
  gameType: GameType;
  status: string;
  p1: { pseudo: string; score: number };
  p2: { pseudo: string; score: number };
};

@Component({
  selector: 'app-livegames',
  templateUrl: './livegames.component.html',
  styleUrls: ['./livegames.component.css'],
})
export class LivegamesComponent implements OnInit {
  _BeLike = BeLike;
  _GameType = GameType;
  pageIndex = 0;
  pageSize = 12;
  pageStart = 0;
  games: Array<GameInfo> = Array<GameInfo>();
  printedGames: Array<GameInfo> = Array<GameInfo>();

  constructor(
    private readonly wss: WebSocketsService,
    private readonly router: Router,
    private client: WebSocketsService,
    private dialog: MatDialog,
  ) {}

  titleMe(game: GameInfo): string {
    return game.p1.pseudo + ' vs ' + game.p2.pseudo;
  }

  changePrintedGames($event: any): void {
    this.pageSize = $event.pageSize;
    this.pageIndex = $event.pageIndex;
    this.pageStart = this.pageIndex * this.pageSize;
    const restGames: number = this.games.length - this.pageIndex * this.pageSize;
    this.printedGames = this.games.slice(
      this.pageStart,
      restGames < this.pageSize ? restGames : this.pageSize,
    );
  }

  ngOnInit(): void {
    this.games = [];
    this.printedGames = [];
    this.client.on('gamesInfos', (data: Array<GameInfo>) => {
      this.games = data;
	  const restGames: number = this.games.length - this.pageIndex * this.pageSize;
	  this.printedGames = this.games.slice(
		this.pageStart,
		restGames < this.pageSize ? restGames : this.pageSize,
	  );
    });
    this.client.on('addGame', (data: GameInfo) => {
      this.games.push(data);
	  const restGames: number = this.games.length - this.pageIndex * this.pageSize;
	  this.printedGames = this.games.slice(
		this.pageStart,
		restGames < this.pageSize ? restGames : this.pageSize,
	  );
    });
    this.client.on('chgGame', (data: GameInfo) => {
      for (const [index, game] of this.games.entries()) {
        if (game.UUID === data.UUID) {
          this.games[index] = data;
		  const restGames: number = this.games.length - this.pageIndex * this.pageSize;
		  this.printedGames = this.games.slice(
			this.pageStart,
			restGames < this.pageSize ? restGames : this.pageSize,
		  );
          break;
        }
      }
    });
    this.client.on('rmvGame', (data: string) => {
      // console.log('rmvGame: ' + data);
      for (const crnt in this.games) {
        if (this.games[crnt].UUID === data) {
          const index: number = this.games.indexOf(this.games[crnt]);
          this.games = this.games.splice(index, 1);
		  const restGames: number = this.games.length - this.pageIndex * this.pageSize;
		  this.printedGames = this.games.slice(
			this.pageStart,
			restGames < this.pageSize ? restGames : this.pageSize,
		  );
          break;
        }
      }
    });
    this.wss.emit('getGamesList');
  }

  errorJoinGame(gameUUID: string, errorReason: string) {
    this.dialog.open(ErrorJoinGameComponent, {
      data: { error: errorReason, gameUUID: gameUUID },
    });
  }

  joinAs(_beLike: BeLike, uuid: string) {
    this.client.on(
      'joinAs',
      (data: { gameUUID: string; errorReason: string }) => {
        this.client.removeListener('joinAs');
        data.errorReason === ''
          ? this.router.navigate(['Game/' + data.gameUUID])
          : this.errorJoinGame(data.gameUUID, data.errorReason);
      },
    );
    // console.log(uuid);
    this.client.emit('playAs', { beLike: _beLike, gameUUID: uuid });
  }
}
