import {
  AfterViewInit,
  Component,
  Input,
  OnChanges,
  SimpleChanges,
  ViewChild,
} from '@angular/core';
import { MatPaginator } from '@angular/material/paginator';
import { MatTableDataSource } from '@angular/material/table';
import { Router } from '@angular/router';
import { WebSocketsService } from '../shared/web-sockets.service';
import { Games } from '../profile/profile.component';

@Component({
  selector: 'app-profile-games',
  templateUrl: './profile-games.component.html',
  styleUrls: ['./profile-games.component.css'],
})
export class ProfileGamesComponent implements OnChanges, AfterViewInit {
  @Input() gameslist: Games[] = [];
  @Input() responsive = false;

  pageIndex = 0;
  pageSize = 0;

  displayedColumns: string[] = ['p1', 'p1_score', 'vs', ' p2_score', 'p2'];
  dataSourceGame = new MatTableDataSource(this.gameslist);

  @ViewChild(MatPaginator) paginator: MatPaginator | undefined;

  constructor(private router: Router, private wss: WebSocketsService) {}

  ngOnChanges(changes: SimpleChanges): void {
    if (changes['gameslist']) {
      this.gameslist = changes['gameslist'].currentValue;
      this.dataSourceGame.data = this.gameslist;
      if (this.paginator !== undefined) {
        this.dataSourceGame.data = this.gameslist.slice(
          this.paginator.pageIndex * this.paginator.pageSize,
          this.paginator.pageIndex * this.paginator.pageSize +
            this.paginator.pageSize,
        );
      }
    }
    if (changes['responsive'] !== undefined) {
      this.responsive = changes['responsive'].currentValue;
      if (this.responsive) {
        this.displayedColumns = ['p1', 'vs', 'p2'];
      } else {
        this.displayedColumns = ['p1', 'p1Score', 'vs', 'p2Score', 'p2'];
      }
    }
  }

  ngAfterViewInit() {
    this.paginator = this.paginator as MatPaginator;
    this.dataSourceGame.paginator = this.paginator;
    if (this.paginator !== undefined) {
      this.dataSourceGame.data = this.gameslist.slice(
        this.paginator.pageIndex * this.paginator.pageSize,
        this.paginator.pageIndex * this.paginator.pageSize +
          this.paginator.pageSize,
      );
    }
  }

  redirect(id: number) {
    this.router.navigate(['Profile/' + id]);
  }

  refresh($event: any) {
    this.dataSourceGame.data = this.gameslist.slice(
      $event.pageIndex * $event.pageSize,
      $event.pageIndex * $event.pageSize + $event.pageSize,
    );
    this.pageIndex = $event.pageIndex;
    this.pageSize = $event.pageSize;
    this.dataSourceGame.data.forEach((element) => {
      this.wss.emit('get-status', {
        id: element.p1.id,
      });
      this.wss.emit('get-status', {
        id: element.p2.id,
      });
    });
  }
}
