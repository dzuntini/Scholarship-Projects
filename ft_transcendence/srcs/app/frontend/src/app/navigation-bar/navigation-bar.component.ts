import { HttpClient } from '@angular/common/http';
import { Component, Input, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { WebSocketsService } from '../shared/web-sockets.service';

export interface User {
  id: number;
  login: string;
  pseudo: string;
  avatar: string;
  elo: number;
  nb_played_game: number;
  nb_defeat: number;
  nb_victory: number;
}

@Component({
  selector: 'app-navigation-bar',
  templateUrl: './navigation-bar.component.html',
  styleUrls: ['./navigation-bar.component.css'],
})
export class NavigationBarComponent implements OnInit {
  constructor(
    private router: Router,
    private http: HttpClient,
    private wss: WebSocketsService,
  ) {}

  @Input() src = '';

  user: User | undefined;

  redirect(dest: string) {
    switch (dest) {
      case '':
      case 'LiveGames':
      case 'Ranking':
      case 'Chat':
        this.router.navigate([dest]);
        break;
      case 'Profile':
        dest += '/' + this.user?.id;
        this.router.navigate([dest]);
        break;
      case 'Logout':
        this.Logout();
        break;
    }
  }

  Logout() {
    this.wss.emit('Logout', undefined);
    localStorage.removeItem('accessToken');
    this.wss.removeListener('client-status-updated');
    this.router.navigate(['Login']);
  }

  ngOnInit(): void {
    this.http.get<User>('/api/appusers/me').subscribe((data) => {
      this.user = data;
      this.wss.emit('get-status', {
        id: data.id,
      });
      this.src = 'data:image/;base64,' + data.avatar;
    });
  }
}
