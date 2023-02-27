import {
  AfterViewInit,
  Component,
  Input,
  OnChanges,
  OnInit,
  SimpleChanges,
  ViewChild,
} from '@angular/core';
import { MatPaginator } from '@angular/material/paginator';
import { MatTableDataSource } from '@angular/material/table';
import { Router } from '@angular/router';
import { User } from '../profile/profile.component';
import { WebSocketsService } from '../shared/web-sockets.service';

@Component({
  selector: 'app-profile-friendlist',
  templateUrl: './profile-friendlist.component.html',
  styleUrls: ['./profile-friendlist.component.css'],
})
export class ProfileFriendlistComponent
  implements OnInit, OnChanges, AfterViewInit
{
  @Input() friendlist: User[] = [];
  @Input() responsive = false;

  displayedColumns: string[] = ['icon', 'login', 'psuedo', 'elo'];
  dataSource = new MatTableDataSource(this.friendlist);

  pageIndex = 0;
  pageSize = 0;

  @ViewChild(MatPaginator) paginator: MatPaginator | undefined;

  constructor(private router: Router, private wss: WebSocketsService) {}

  ngOnInit(): void {
    this.dataSource.filterPredicate = function (data, filter: string): boolean {
      return (
        data.login.toLowerCase().includes(filter) ||
        data.pseudo.toLowerCase().includes(filter) ||
        data.elo.toString() === filter
      );
    };
  }

  ngOnChanges(changes: SimpleChanges): void {
    if (changes['friendlist']) {
      this.friendlist = changes['friendlist'].currentValue;
      this.dataSource.data = this.friendlist;
      // eslint-disable-next-line @typescript-eslint/no-unused-vars
      this.friendlist.forEach((_u, id, _a) => {
        this.wss.emit('get-status', {
          id: id,
        });
      });
    }
    if (changes['responsive'] !== undefined) {
      this.responsive = changes['responsive'].currentValue;
      if (this.responsive) {
        this.displayedColumns = ['icon', 'psuedo'];
      } else {
        this.displayedColumns = ['icon', 'login', 'psuedo', 'elo'];
      }
    }
  }

  ngAfterViewInit() {
    this.dataSource.paginator = this.paginator as MatPaginator;
  }

  applyFilter(event: Event) {
    const filterValue = (event.target as HTMLInputElement).value;
    this.dataSource.filter = filterValue.trim().toLowerCase();

    if (this.dataSource.paginator) {
      this.dataSource.paginator.firstPage();
    }
  }

  redirect(id: number) {
    this.router.navigate(['Profile/' + id]);
  }

  refresh($event: any) {
    this.dataSource.data = this.friendlist.slice(
      $event.pageIndex * $event.pageSize,
      $event.pageIndex * $event.pageSize + $event.pageSize,
    );
    this.pageIndex = $event.pageIndex;
    this.pageSize = $event.pageSize;
    this.dataSource.data.forEach((element) => {
      this.wss.emit('get-status', {
        id: element.id,
      });
      this.wss.emit('get-status', {
        id: element.id,
      });
    });
  }
}
