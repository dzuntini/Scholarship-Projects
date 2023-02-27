import { Component, OnInit } from '@angular/core';
import { validator } from './shared/auth.guard';
import { HttpClient } from '@angular/common/http';
import { WebSocketsService } from './shared/web-sockets.service';
import { Router } from '@angular/router';
import { MatDialog } from '@angular/material/dialog';
import { ErrorPopupComponent } from './error-popup/error-popup.component';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
})
export class AppComponent implements OnInit {
  title = 'frontend';

  constructor(
    private http: HttpClient,
    private wss: WebSocketsService,
    private router: Router,
    public dialog: MatDialog,
  ) {}

  ngOnInit(): void {
    this.wss.forceDisconnectListener();
    if (localStorage.getItem('accessToken') !== null) {
      this.http.get<validator>('/api/auth/verify').subscribe({
        next: (data) => {
          if (data.valid) {
            this.wss.on(
              'validedAuthentication',
              // eslint-disable-next-line @typescript-eslint/no-unused-vars
              (_data: { validation: string }) => {
                this.wss.removeListener('validedAuthentication');
              },
            );
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
            this.wss.on('refresh-client-list', () => {
              this.wss.emit('associateIDtoSocket', {
                token: localStorage.getItem('accessToken'),
              });
            });
            this.wss.emit('associateIDtoSocket', {
              token: localStorage.getItem('accessToken'),
            });
          }
        },
      });
      this.wss.on('generalErrorMessage', (data: string) => {
        this.dialog.open(ErrorPopupComponent, {
          data: { error: data },
        });
      });
    }
  }
}
