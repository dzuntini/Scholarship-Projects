import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { MatTableDataSource } from '@angular/material/table';
import { Router } from '@angular/router';
import { User } from '../profile/profile.component';
import { WebSocketsService } from '../shared/web-sockets.service';

export interface Player {
  name: string;
  elo: number;
}

@Component({
  selector: 'app-ranking',
  templateUrl: './ranking.component.html',
  styleUrls: ['./ranking.component.css'],
})
export class RankingComponent implements OnInit {
  board: User[] = [];
  users: User[] = [];
  pageSize = 10;
  pageIndex = 0;
  responsive = false;

  displayedColumns: string[] = ['icon', 'login', 'psuedo', 'elo'];
  dataSource = new MatTableDataSource(this.board);

  constructor(
    private http: HttpClient,
    private router: Router,
    private wss: WebSocketsService,
  ) {}

  ngOnInit(): void {
    this.http.get<User[]>('/api/appusers/leaderboard').subscribe((data) => {
      // console.log(data);
      this.users = data;
      this.board = this.users.slice(0, 10);
      this.dataSource.data = this.board;
      this.dataSource.data.forEach((element) => {
        this.wss.emit('get-status', {
          id: element.id,
        });
      });
    });
  }

  handleSize(event: any) {
    this.responsive = event.target.innerWidth <= 600;
  }

  onPageChange($event: any) {
    this.board = this.users.slice(
      $event.pageIndex * $event.pageSize,
      $event.pageIndex * $event.pageSize + $event.pageSize,
    );
    this.pageSize = $event.pageSize;
    this.pageIndex = $event.pageIndex;
    this.dataSource.data = this.board;
    this.dataSource.data.forEach((element) => {
      this.wss.emit('get-status', {
        id: element.id,
      });
    });
  }

  redirect(id: number) {
    this.router.navigate(['Profile/' + id]);
  }
}
