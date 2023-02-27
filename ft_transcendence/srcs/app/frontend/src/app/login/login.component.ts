import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { validator } from '../shared/auth.guard';
import { WebSocketsService } from '../shared/web-sockets.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css'],
})
export class LoginComponent implements OnInit {
  constructor(
    private router: Router,
    private wss: WebSocketsService,
    private http: HttpClient,
  ) {}

  redirect() {
    window.open(
      '/api/auth/login',
      'mywindow',
      'location=1,status=1,scrollbars=1,width=800,height=800',
    );
    window.addEventListener('storage', (event) => {
      if (event.key === 'accessToken') {
        this.wss.on('validedAuthentication', (data: { validation: string }) => {
          this.wss.removeListener('validedAuthentication');
          this.router.navigate(['Home']);
        });
        this.wss.on('client-status-updated', (data: any) => {
          const statuses = document.getElementsByClassName(
            'avatar-status-' + data.id,
          );
          if (data.status === 0) {
            for (let i = 0; i < statuses.length; i++) {
              statuses.item(i)?.classList.remove('avatar-status-online');
              statuses.item(i)?.classList.remove('avatar-status-ingame');
              statuses.item(i)?.classList.add('avatar-status-offline');
            }
          } else if (data.status === 1) {
            for (let i = 0; i < statuses.length; i++) {
              statuses.item(i)?.classList.remove('avatar-status-offline');
              statuses.item(i)?.classList.remove('avatar-status-ingame');
              statuses.item(i)?.classList.add('avatar-status-online');
            }
          } else {
            for (let i = 0; i < statuses.length; i++) {
              statuses.item(i)?.classList.remove('avatar-status-online');
              statuses.item(i)?.classList.remove('avatar-status-offline');
              statuses.item(i)?.classList.add('avatar-status-ingame');
            }
          }
        });
        this.wss.emit('associateIDtoSocket', { token: event.newValue });
      }
    });
  }

  ngOnInit(): void {
    this.wss.forceDisconnectListener();
    if (localStorage.getItem('accessToken') !== null) {
      this.http.get<validator>('/api/auth/verify').subscribe({
        next: (data) => {
          if (data.valid === true && data.isAuthed === true) {
            this.router.navigate(['Home']);
          } else if (data.valid === true && data.isAuthed === false) {
            this.router.navigate(['2FA']);
          }
        },
      });
    }
    this.wss.generalListener();
  }
}
