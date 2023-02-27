/* eslint-disable @typescript-eslint/no-empty-function */
import { AfterViewInit, Component, OnDestroy, OnInit } from '@angular/core';
import { WebSocketsService } from '../shared/web-sockets.service';
import { Router } from '@angular/router';
import { BeLike, GameType } from '../livegames/livegames.component';

export interface Tile {
  class: string;
  text: string;
  beLike: BeLike;
  gameType: GameType;
  waiting: boolean;
}

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css'],
})
export class HomeComponent implements OnInit, AfterViewInit, OnDestroy {
  homeGrid: object = document.getElementsByClassName('home-grid')[0];

  public tiles: Tile[] = [
    {
      class: 'game-tiles',
      text: 'unranked game',
      beLike: BeLike.Player,
      gameType: GameType.unranked,
      waiting: false,
    },
    {
      class: 'game-tiles',
      text: 'ranked game',
      beLike: BeLike.Player,
      gameType: GameType.ranked,
      waiting: false,
    },
  ];

  public waitChal: string[] = ['Waiting for', 'a chalenger'];

  constructor(private router: Router, private client: WebSocketsService) {}

  _BeLike = BeLike;

  ngOnInit(): void {}

  ngAfterViewInit(): void {}

  resetTiles(): void {
    this.tiles[0].waiting = false;
    this.tiles[1].waiting = false;
  }

  //freeMapGame() {
  //  this.client.emit('freeGames');
  //}

  errorJoinGame(gameUUID: string, errorReason: string) {
    const errorPopup: HTMLDivElement = document.createElement('div');
    errorPopup.className = 'errorJoinGame';
    errorPopup.innerHTML =
      'error with GameID: ' + gameUUID + ' for reason: ' + errorReason;
    document.getElementsByClassName('game-grid')[0]!.appendChild(errorPopup);
  }

  joinAs(beLike: BeLike, gameType: GameType) {
    this.client.on(
      'joinAs',
      (data: { gameUUID: string; errorReason: string }) => {
        this.client.removeListener('joinAs');
        this.router.navigate(['Game/' + data.gameUUID]);
      },
    );
    this.resetTiles();
    this.tiles[gameType ? 1 : 0].waiting = true;
    this.client.emit('playAs', { beLike: beLike, gameUUID: '', gameType });
  }

  ngOnDestroy(): void {
    this.client.removeListener('joinAs');
  }
}
