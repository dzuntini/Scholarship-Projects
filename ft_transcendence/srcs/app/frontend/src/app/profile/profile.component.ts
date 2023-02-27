import { HttpClient } from '@angular/common/http';
import { Component, Input, OnInit, ViewChild } from '@angular/core';
import { FormBuilder, Validators } from '@angular/forms';
import { MatTable } from '@angular/material/table';
import { ActivatedRoute, Router } from '@angular/router';
import { encode } from 'base64-arraybuffer';
import { WebSocketsService } from '../shared/web-sockets.service';
import { MatDialog } from '@angular/material/dialog';
import { ErrorPopupComponent } from '../error-popup/error-popup.component';

export interface User {
  id: number;
  login: string;
  pseudo: string;
  avatar: string;
  twoFactorAuthEnabled: boolean;
  elo: number;
  nb_played_game: number;
  nb_defeat: number;
  nb_victory: number;
}

export interface Games {
  p1: User;
  p1_score: number;
  vs: string;
  p2_score: number;
  p2: User;
}

@Component({
  selector: 'app-profile',
  templateUrl: './profile.component.html',
  styleUrls: ['./profile.component.css'],
})
export class ProfileComponent implements OnInit {
  displayedColumns: string[] = ['Login', 'Pseudo', 'Elo'];
  friendlist: User[] = [];
  gamelist: Games[] = [];
  ishemyfriend = false;
  isheblocked = false;

  @ViewChild(MatTable) table: MatTable<User> | undefined;
  @Input() src = '';
  myFace: string = this.src;
  @Input() user: User = {
    id: -1,
    login: '',
    pseudo: '',
    avatar: '',
    elo: -1,
    nb_defeat: -1,
    nb_played_game: -1,
    nb_victory: -1,
    twoFactorAuthEnabled: false,
  };

  image = '';
  qrcode = '';
  responsive = false;
  mine = true;
  error = '';
  perror = '';

  respseudochange = this.formBuilder.group({
    pseudo: this.formBuilder.control('', [Validators.required]),
  });

  unrespseudochange = this.formBuilder.group({
    pseudo: this.formBuilder.control('', [Validators.required]),
  });

  res2fatoggler = this.formBuilder.group({
    code: this.formBuilder.control('', [
      Validators.required,
      Validators.maxLength(6),
      Validators.minLength(6),
      Validators.pattern('[0-9]{6}'),
    ]),
  });

  unres2fatoggler = this.formBuilder.group({
    code: this.formBuilder.control('', [
      Validators.required,
      Validators.maxLength(6),
      Validators.minLength(6),
      Validators.pattern('[0-9]{6}'),
    ]),
  });

  constructor(
    private http: HttpClient,
    private formBuilder: FormBuilder,
    private route: ActivatedRoute,
    private router: Router,
    private wss: WebSocketsService,
    private dialog: MatDialog,
  ) {}

  ngOnInit(): void {
    this.http.get<User>('/api/appusers/me').subscribe((data) => {
      this.user = data;
      this.route.params.subscribe((params) => {
        this.user = data;
        if (Number.isNaN(+params['id'])) {
          this.router.navigate(['Profile/' + this.user.id]);
        } else if (+params['id'] === this.user.id) {
          this.mine = true;
          this.src = 'data:image/;base64,' + data.avatar;
          this.myFace = this.src;
          this.http
            .get('/api/2fa/generate', {
              responseType: 'arraybuffer',
            })
            .subscribe(
              (data) => (this.qrcode = 'data:image/;base64,' + encode(data)),
            );
          this.http
            .get<User[]>('/api/appusers/me/friends')
            .subscribe((data) => {
              this.friendlist = data;
              this.friendlist.forEach((element) => {
                this.wss.emit('get-status', {
                  id: element.id,
                });
              });
            });
          this.http.get<any[]>('/api/appusers/me/player').subscribe((data) => {
            this.gamelist = [];
            data.forEach((element) => {
              this.gamelist.push({
                p1: element.players.Player1,
                p1_score: element.p1_score as number,
                vs: 'vs',
                p2_score: element.p2_score as number,
                p2: element.players.Player2 as User,
              });
            });
          });
        } else {
          this.mine = false;
          this.http
            .get<User>('/api/appusers/' + params['id'])
            .subscribe((data) => {
              this.user = data;
              this.src = 'data:image/;base64,' + data.avatar;
              this.http
                .get<User[]>('/api/appusers/' + params['id'] + '/friends')
                .subscribe((data) => {
                  this.friendlist = data;
                });
              this.http
                .get<{ friend: boolean }>(
                  '/api/appusers/' + params['id'] + '/myfriend',
                )
                .subscribe((data) => {
                  this.ishemyfriend = data.friend;
                });
              this.http
                .get<{ blocked: boolean }>(
                  '/api/appusers/' + params['id'] + '/blockedbyme',
                )
                .subscribe((data) => {
                  this.isheblocked = data.blocked;
                });
              this.http
                .get<any[]>('/api/appusers/' + params['id'] + '/player')
                .subscribe((data) => {
                  this.gamelist = [];
                  data.forEach((element) => {
                    this.gamelist.push({
                      p1: element.players.Player1 as User,
                      p1_score: element.p1_score as number,
                      vs: 'vs',
                      p2_score: element.p2_score as number,
                      p2: element.players.Player2 as User,
                    });
                  });
                });
            });
        }
      });
    });
    this.responsive = window.innerWidth <= 1200;
  }

  handleSize(event: any) {
    this.responsive = event.target.innerWidth <= 1200;
  }

  reschangePseudo() {
    if (this.respseudochange.valid) {
      this.http
        .patch<User>('/api/appusers/me', {
          pseudo: this.respseudochange.value.pseudo,
        })
        .subscribe({
          next: (data) => {
            this.perror = '';
            this.user.pseudo = data.pseudo;
            this.respseudochange.controls['pseudo'].setErrors(null);
          },
          error: () => {
            this.perror = ': User already has that name!';
            this.dialog.open(ErrorPopupComponent, {
              data: { error: "Can't have the same name as another user!" },
            });
            this.respseudochange.controls['pseudo'].setErrors({
              notUnique: true,
            });
          },
        });
    }
  }

  unreschangePseudo() {
    if (this.unrespseudochange.valid) {
      this.http
        .patch<User>('/api/appusers/me', {
          pseudo: this.unrespseudochange.value.pseudo,
        })
        .subscribe({
          next: (data) => {
            this.perror = '';
            this.user.pseudo = data.pseudo;
            this.unrespseudochange.controls['pseudo'].setErrors(null);
          },
          error: () => {
            this.perror = ': User already has that name!';
            this.dialog.open(ErrorPopupComponent, {
              data: { error: "Can't have the same name as another user!" },
            });
            this.unrespseudochange.controls['pseudo'].setErrors({
              notUnique: true,
            });
          },
        });
    }
  }

  res2faToggler() {
    if (this.res2fatoggler.valid) {
      this.http
        .patch<User>('/api/2fa/toggle', {
          twoFactorAuthenticationCode: this.res2fatoggler.value.code,
        })
        .subscribe({
          next: () => {
            this.error = '';
            this.user.twoFactorAuthEnabled = !this.user.twoFactorAuthEnabled;
            this.res2fatoggler.controls['code'].setErrors(null);
          },
          error: () => {
            this.error = ': Invalid 2FA Code!';
            this.dialog.open(ErrorPopupComponent, {
              data: { error: 'Invalid 2fa Code!' },
            });
            this.res2fatoggler.controls['code'].setErrors({ incorrect: true });
          },
        });
    }
  }

  unres2faToggler() {
    if (this.unres2fatoggler.valid) {
      this.http
        .patch<User>('/api/2fa/toggle', {
          twoFactorAuthenticationCode: this.unres2fatoggler.value.code,
        })
        .subscribe({
          next: () => {
            this.error = '';
            this.user.twoFactorAuthEnabled = !this.user.twoFactorAuthEnabled;
            this.unres2fatoggler.controls['code'].setErrors(null);
          },
          error: () => {
            this.error = ': Invalid 2FA Code!';
            this.dialog.open(ErrorPopupComponent, {
              data: { error: 'Invalid 2fa Code!' },
            });
            this.unres2fatoggler.controls['code'].setErrors({
              incorrect: true,
            });
          },
        });
    }
  }

  addFriend() {
    this.http
      .patch<User>('/api/appusers/me/addfriend/' + this.user.id, {})
      .subscribe({
        error: () => {
          this.ishemyfriend = false;
          this.dialog.open(ErrorPopupComponent, {
            data: { error: "Can't add friend!" },
          });
        },
        next: () => {
          this.ishemyfriend = true;
        },
      });
  }

  removeFriend() {
    this.http
      .patch<User>('/api/appusers/me/removefriend/' + this.user.id, {})
      .subscribe({
        error: () => {
          this.ishemyfriend = true;
          this.dialog.open(ErrorPopupComponent, {
            data: { error: "Can't remove friend!" },
          });
        },
        next: () => {
          this.ishemyfriend = false;
        },
      });
  }

  block() {
    this.http
      .patch<User>('/api/appusers/me/block/' + this.user.id, {})
      .subscribe({
        error: () => {
          this.isheblocked = false;
          this.dialog.open(ErrorPopupComponent, {
            data: { error: "Can't block user!" },
          });
        },
        next: () => {
          this.isheblocked = true;
        },
      });
  }

  unblock() {
    this.http
      .patch<User>('/api/appusers/me/unblock/' + this.user.id, {})
      .subscribe({
        error: () => {
          this.isheblocked = true;
          this.dialog.open(ErrorPopupComponent, {
            data: { error: "Can't unblock user!" },
          });
        },
        next: () => {
          this.isheblocked = false;
        },
      });
  }

  changeImage(event: any) {
    const file: File = event.target.files[0];
    if (file) {
      if (file.type.includes('image') && file.size <= 5000000) {
        this.image = file.name;
        const reader = new FileReader();
        reader.readAsDataURL(file);
        setTimeout(() => {
          let b64 = reader.result?.toString();
          b64 = b64?.replace(/^[^*,]*,/, '');
          this.http
            .patch<User>('/api/appusers/me', { avatar: b64 })
            .subscribe((data: User) => {
              this.src = 'data:image/;base64,' + data.avatar;
              this.myFace = this.src;
            });
        }, 2000);
        reader.onerror = function (error) {
          // console.log('Error: ', error);
        };
      } else {
        this.image = 'Error : Incorrect File or File Size Superior to 5mb';
      }
    }
  }

  refresh($event: any) {
    switch ($event.index) {
      case 0:
        this.friendlist.forEach((element) => {
          this.wss.emit('get-status', {
            id: element.id,
          });
        });
        break;
      case 1:
        this.gamelist.forEach((element) => {
          this.wss.emit('get-status', {
            id: element.p1.id,
          });
          this.wss.emit('get-status', {
            id: element.p2.id,
          });
        });
        break;
    }
  }
}
