/* eslint-disable @typescript-eslint/no-non-null-assertion */
/* eslint-disable @typescript-eslint/no-unused-vars */
import {
  AfterViewChecked,
  AfterViewInit,
  Component,
  OnDestroy,
  OnInit,
  SecurityContext,
} from '@angular/core';

import { HttpClient } from '@angular/common/http';
import { Input } from '@angular/core';
import { WebSocketsService } from '../shared/web-sockets.service';
import { MatDialog } from '@angular/material/dialog';
import { ChatRoomCreateRoom } from '../chatroom-create-room/chatroom-create-room.component';
import { ChatRoomDeleteRoom } from '../chatroom-delete-room/chatroom-delete-room.component';
import { ChatRoomJoinRoom } from '../chatroom-join-room/chatroom-join-room.component';
import { Router } from '@angular/router';
import { ChatRoomModifyRoom } from '../chatroom-modify-room/chatroom-modify-room.component';
import { GameType } from '../livegames/livegames.component';
import { DomSanitizer } from '@angular/platform-browser';
import { ErrorPopupComponent } from '../error-popup/error-popup.component';
import { ChatroomJoinPasswordComponent } from '../chatroom-join-password/chatroom-join-password.component';

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

export interface Rooms {
  id: number;
  name: string;
  haspass?: boolean;
  isdm?: boolean;
  visible?: boolean;
  password?: string;
  ownerID?: number;
  Access: {
    AuthorizationID: number;
    appuserID: number;
    roomID: number;
  }[];
}

export interface CreateDialogData {
  name: string;
  id: number;
  password: string | undefined;
  visible: boolean;
}

export interface DelDialogData {
  room: string;
  id: number;
}

export interface ModDialogData {
  id: number;
  room: string;
  password: string;
  visible: boolean;
}

export interface Tile {
  text: string;
  value: Rooms;
  visible: boolean;
}

@Component({
  selector: 'app-chatroom',
  templateUrl: './chatroom.component.html',
  styleUrls: ['./chatroom.component.css'],
})
export class ChatRoomComponent
  implements OnInit, AfterViewInit, AfterViewChecked, OnDestroy
{
  message = '';

  @Input() user: User = {
    id: 1,
    login: '',
    pseudo: '',
    avatar: '',
    elo: -1,
    nb_defeat: -1,
    nb_played_game: -1,
    nb_victory: -1,
    twoFactorAuthEnabled: false,
  };

  @Input() current_room: Rooms = {
    id: -1,
    name: 'Draft',
    password: '',
    visible: true,
    ownerID: -1,
    Access: [],
  };

  public roomsList: Rooms[] = [];
  private usersList: User[] = [];
  public messagesList: HTMLElement[] = [];
  public channelUsers: User[] = [];
  private usersblocked: number[] = [];
  gameType = GameType;

  constructor(
    private wss: WebSocketsService,
    private http: HttpClient,
    public dialog: MatDialog,
    private router: Router,
    private sanitizer: DomSanitizer,
  ) {}

  appendToMessage(htmlElem: HTMLElement): void {
    const messagesListSpan: HTMLSpanElement = (
      document.getElementsByClassName(
        'chat-messages-list',
      ) as HTMLCollectionOf<HTMLSpanElement>
    )[0];
    if (messagesListSpan === null || messagesListSpan === undefined) return;
    messagesListSpan.appendChild(htmlElem);
  }

  invitGameButton(invitGame: string): boolean {
    // console.log('invitGameButton');
    if (!invitGame.startsWith('\\invitation-')) return false;
    // console.log('invitGameButton');
    const datasInvit: string[] = invitGame.split('-');
    if (datasInvit.length < 4) return false;
    const hostID: number = +datasInvit[1];
    if (hostID !== this.user.id) {
      const hostPseudo: string | null = this.sanitizer.sanitize(
        SecurityContext.HTML,
        this.getUserbyID(hostID)!.pseudo,
      );
      if (hostPseudo === null) return false;
      const gameT: GameType = +datasInvit[2];
      const gameUUID: string = invitGame.slice(
        ('\\invitation-' + hostID + '-' + gameT + '-').length,
      );
      // console.log('invitGameButton: ' + gameUUID);
      const gameButton: HTMLButtonElement = document.createElement('button');
      gameButton.className = 'chat-message-button';
      gameButton.innerHTML =
        hostPseudo +
        "'s invitation to a " +
        (gameT ? 'ranked' : 'unranked') +
        ' game';
      gameButton.addEventListener('click', () => this.AcceptGame(gameUUID));
      this.appendToMessage(gameButton);
      return true;
    } else {
      const guestID =
        this.user.id !== this.current_room.Access[0].appuserID
          ? this.current_room.Access[0].appuserID
          : this.current_room.Access[1].appuserID;
      const guestPseudo: string | null = this.sanitizer.sanitize(
        SecurityContext.HTML,
        this.getUserbyID(guestID)!.pseudo,
      );
      if (guestPseudo !== null) {
        const gameT: GameType = +datasInvit[2];
        this.paragraphMessage(
          'You invite ' +
            guestPseudo +
            ' to a ' +
            (gameT ? 'ranked' : 'unranked') +
            ' game',
        );
      }
      return true;
    }
  }

  paragraphMessage(message: string) {
    // console.log('paragraphMessage');
    const sanitizedMessage: string | null = this.sanitizer.sanitize(
      SecurityContext.HTML,
      message,
    );
    if (sanitizedMessage === null) return;
    const messagePara: HTMLParagraphElement = document.createElement('p');
    messagePara.className = 'chat-message-message';
    messagePara.innerHTML = sanitizedMessage;
    this.appendToMessage(messagePara);
  }

  getAllMessagesInRoom(roomID: number) {
    this.http.get('/api/rooms/messages/' + roomID).subscribe((result: any) => {
      const messagesListSpan: HTMLSpanElement = (
        document.getElementsByClassName(
          'chat-messages-list',
        ) as HTMLCollectionOf<HTMLSpanElement>
      )[0];
      messagesListSpan.replaceChildren();
      this.messagesList = [];
      // console.log('Data de ' + roomID);
      // console.log(result);
      for (const mess in result) {
        // console.log(result[mess].content);
        if (!this.usersblocked.includes(result[mess].appuserID))
          if (!this.invitGameButton(result[mess].content))
            this.paragraphMessage(
              result[mess].appuser.pseudo + ': ' + result[mess].content,
            );
      }
    });
  }

  ngOnInit(): void {
    /*Init*/
    this.wss.on('connectedChat', () => {
      this.wss.removeListener('connectedChat');
      this.http.get<User>('/api/appusers/me').subscribe((data) => {
        this.user = data;

        /*Listener*/
        this.wss.on(
          'message-received',
          (data: { id: number; message: string }) => {
            let user = '';
            this.http
              .get<User>('/api/appusers/' + data.id)
              .subscribe((result: User) => {
                user = result.pseudo;
                if (this.usersblocked.includes(data.id)) return;
                if (!this.invitGameButton(data.message))
                  this.paragraphMessage(user + ': ' + data.message);
              });
          },
        );

        this.wss.on('rooms-updated', () => {
          this.makeRoomsList();
        });

        this.wss.on('reset-draft', () => {
          this.resetDraft();
        });

        /*For Everyone */
        this.wss.on(
          'user-status',
          (data: { channelID: number; userID: number }) => {
            // console.log('/api/rooms/' + data.channelID);
            this.http
              .get<Rooms>('/api/rooms/' + data.channelID)
              .subscribe((room: Rooms) => {
                room.name = this.getRoomName(room);
                this.current_room = room;
                // console.log(room);
                // console.log('/api/rooms/members/' + this.current_room.id);
                this.http
                  .get<User[]>('/api/rooms/members/' + this.current_room.id)
                  .subscribe((users: User[]) => {
                    this.channelUsers = [];
                    this.channelUsers = users;
                    // console.log(users);
                    if (data.userID && data.userID === this.user.id) {
                      //this.ListUserJoinedRoom(this.current_room.id);
                      this.getAllMessagesInRoom(this.current_room.id);
                      this.makeRoomsList();
                    }
                    // console.log(users);
                  });
              });
            // console.log('coucou user-status');
          },
        );

        /* Only for current user */
        this.wss.on('fail-join', (data: any) => {
          this.dialog.open(ErrorPopupComponent, {
            data: { error: data.message },
          });
        });

        /*Delete the enter issue*/
        const a = document.getElementById('chat-area') as HTMLTextAreaElement;
        a.addEventListener('keypress', function (event) {
          if (
            event.code === 'enter' ||
            event.code === 'Enter' ||
            event.key === 'enter' ||
            event.key === 'Enter'
          )
            event.preventDefault();
        });

        this.http.get<User[]>('api/appusers').subscribe((data: User[]) => {
          this.usersList = data;
          this.channelUsers = this.usersList;
          this.makeRoomsList();
        });
        this.getblocked();
      });
    });
    this.wss.emit('connect-chat');
  }

  ngAfterViewInit(): void {
    this.scrollToBottom('room-list');
  }

  ngAfterViewChecked() {
    this.scrollToBottom2('message-list');
  }

  ngOnDestroy() {
    this.wss.removeListener('message-received');
    this.wss.removeListener('rooms-updated');
    this.wss.removeListener('join-success');
    this.wss.removeListener('fail-join');
    this.wss.removeListener('reset-draft');
    this.wss.removeListener('user-status');
    this.wss.emit('chat-leave-room');
  }

  resetDraft() {
    this.http.get<User[]>('api/appusers').subscribe((data: User[]) => {
      this.usersList = data;
      this.channelUsers = this.usersList;
      this.current_room.id = -1;
      this.current_room.name = 'Draft';
      const messagesListSpan: HTMLSpanElement = (
        document.getElementsByClassName(
          'chat-messages-list',
        ) as HTMLCollectionOf<HTMLSpanElement>
      )[0];
      messagesListSpan.replaceChildren();
      this.messagesList = [];
      this.makeRoomsList();
    });
  }

  draft() {
    this.wss.emit('chat-leave-room');
    this.resetDraft();
  }

  SendMessage(invitGame: string | undefined) {
    this.message = invitGame !== undefined ? invitGame : this.message;
    // console.log('SendMessage: ' + this.message);
    if (this.current_room.id === -1) this.paragraphMessage(this.message);
    else if (this.message !== '') {
      this.wss.emit('sendMessage', {
        message: this.message,
        user: this.user.pseudo,
        roomID: this.current_room.id,
      });
    }
    this.message = '';
  }

  ListUserJoinedRoom(channelID: number) {
    this.http
      .get<User[]>('/api/rooms/members/' + channelID)
      .subscribe((users: User[]) => {
        this.channelUsers = users;
      });
  }

  /*When clicking on a room*/
  JoinRoom(channelID: number) {
    if (channelID !== this.current_room.id) {
      this.wss.emit('chat-joinroom', {
        channelID: channelID,
      });
    }
  }

  JoinRoomList(channelID: number, haspass: boolean | undefined) {
    // console.log('/api/appusers/me/member/' + channelID);
    this.http.get<Rooms>('/api/appusers/me/member/' + channelID).subscribe({
      next: (data) => {
        this.JoinRoom(data.id);
      },
      error: (err) => {
        if (haspass === true) {
          const dialogRef = this.dialog.open(ChatroomJoinPasswordComponent, {
            data: { name: this.getRoomByID(channelID)?.name },
          });
          dialogRef.afterClosed().subscribe((result) => {
            if (result != undefined) {
              // console.log('/api/rooms/join/' + channelID);
              this.http
                .patch<Rooms>('/api/rooms/join/' + channelID, {
                  password: result.password,
                })
                .subscribe({
                  next: (room) => {
                    // console.log('Joined room ' + room.name);
                    this.JoinRoom(room.id);
                  },
                  error: () => {
                    // console.log(err);
                    this.dialog.open(ErrorPopupComponent, {
                      data: { error: err.error.message },
                    });
                  },
                });
            }
          });
        } else {
          // console.log('/api/rooms/join/' + channelID);
          this.http.patch<Rooms>('/api/rooms/join/' + channelID, {}).subscribe({
            next: (room) => {
              // console.log('Joined room ' + room.name);
              this.JoinRoom(room.id);
            },
            error: () => {
              // console.log(err);
              this.dialog.open(ErrorPopupComponent, {
                data: { error: err.error.message },
              });
            },
          });
        }
      },
    });
  }

  JoinRoomButton() {
    let jrname;
    let pass;
    const dialogRef = this.dialog.open(ChatRoomJoinRoom, {
      panelClass: 'custom-dialog-container',
      data: { name: jrname, password: pass },
    });

    dialogRef.afterClosed().subscribe((result) => {
      // console.log(result);
      if (result !== undefined && result.name !== undefined) {
        this.http
          .get<{ id: number }>('/api/rooms/byName/' + result.name)
          .subscribe({
            next: (id) => {
              this.http
                .patch<Rooms>('/api/rooms/join/' + id.id, {
                  password: result.password,
                })
                .subscribe({
                  next: (room) => {
                    // console.log('Joined room ' + room.name);
                    this.JoinRoom(room.id);
                  },
                  error: (err) => {
                    // console.log(err);
                    this.dialog.open(ErrorPopupComponent, {
                      data: { error: err.error.message },
                    });
                  },
                });
            },
            error: (err) => {
              // console.log(err);
              this.dialog.open(ErrorPopupComponent, {
                data: { error: err.error.message },
              });
            },
          });
      }
    });
  }

  /*Pop up when click on addRoom*/
  CreateRoom() {
    const crntName = '';
    const pass = '';
    const id = 0;
    const visible = true;

    const dialogRef = this.dialog.open(ChatRoomCreateRoom, {
      panelClass: 'create-dialog-container',
      data: { name: crntName, password: pass, visible: visible },
    });
    dialogRef.afterClosed().subscribe((result) => {
      // console.log(result);
      if (result) {
        this.http
          .post<Rooms>('/api/rooms', {
            name: result.name,
            password: result.password,
            visible: result.visible,
          })
          .subscribe({
            next: (chatRoom: Rooms) => {
              this.wss.on('chat-redirection', (data: string) => {
                this.wss.removeListener('chat-redirection');
                this.wss.emit('chat-joinroom', {
                  room: chatRoom.name,
                  id: chatRoom.id,
                  password: data,
                });
              });
              this.wss.emit('chat-update-room', { redirect: true });
            },
            error: (err) => {
              // console.log(err);
              this.dialog.open(ErrorPopupComponent, {
                data: { error: err.error.message },
              });
            },
          });
      }
    });
  }

  ModifyRoom() {
    if (this.searchStatus(this.user.id) === 1 && this.current_room.id != -1) {
      const room = this.current_room.name;
      const password = this.current_room.password;
      const visible = this.current_room.visible;
      const id = this.current_room.id;
      const dialogRef = this.dialog.open(ChatRoomModifyRoom, {
        panelClass: 'create-dialog-container',
        data: { room: room, password: password, visible: visible, id: id },
      });
      dialogRef.afterClosed().subscribe((result) => {
        if (result && result.id !== -1) {
          this.current_room.name = result.room;
          if (result.password !== undefined)
            this.current_room.password = result.password;
          this.current_room.visible = result.visible;
        }
      });
    }
  }

  /*Pop up when delete room*/
  DeleteRoom() {
    // console.log(this.current_room.ownerID + ' ' + this.user.id);
    if (this.searchStatus(this.user.id) === 1 && this.current_room.id != -1) {
      const cr = this.current_room.name;
      const crid = this.current_room.id;
      const dialogRef = this.dialog.open(ChatRoomDeleteRoom, {
        panelClass: 'custom-dialog-container',
        data: { room: cr, id: crid },
      });
    }
  }

  /*
   ** Profile Commands------------------------------------------------------------------------------------
   **Pop up when clickin/hovering on user
   */

  redirect(user: User) {
    this.router.navigate(['Profile/' + user.id]);
  }

  dmWithSomeone(user: User) {
    this.http.get<Rooms>('/api/appusers/me/hasdm/' + user.id).subscribe({
      next: (room) => {
        this.JoinRoom(room.id);
      },
      error: (err) => {
        if (err.error.statusCode === 403) {
          this.dialog.open(ErrorPopupComponent, {
            data: { error: err.error.message },
          });
        } else {
          this.http
            .post<Rooms>('/api/rooms/createDM', {
              otherId: user.id,
            })
            .subscribe({
              next: (chatRoom) => {
                this.wss.on('chat-redirection', () => {
                  this.wss.removeListener('chat-redirection');
                  this.JoinRoom(chatRoom.id);
                });
                this.wss.emit('chat-update-room', { redirect: true });
                // console.log(chatRoom);
              },
              error: (err) => {
                this.dialog.open(ErrorPopupComponent, {
                  data: { error: err.error.message },
                });
              },
            });
        }
      },
    });
  }

  // BLOCK POUR JOINGAME
  // Ma facon de gerer les erreur de join game
  AcceptGame(gameUUID: string | undefined) {
    if (gameUUID !== undefined) {
      this.wss.on('joinAs', (gameUUID: string) => {
        this.wss.removeListener('joinAs');
        this.router.navigate(['Game/' + gameUUID]);
      });
      this.wss.emit('acceptGame', { gameUUID: gameUUID });
    }
  }

  InvitGame(guestID: number, gameType: GameType) {
    // console.log(guestID);
    // console.log(gameType);
    if (guestID !== undefined && gameType !== undefined) {
      this.wss.on('joinAs', (gameUUID: string) => {
        this.wss.removeListener('joinAs');
        this.router.navigate(['Game/' + gameUUID]);
      });
      // console.log(
      //  'InvitGame - guestID: ' + guestID + ' - gameType: ' + gameType,
      // );
      this.wss.emit('invitGame', { guestID: guestID, gameType: gameType });
    }
  }

  // FIN DU BLOCK POUR JOINGAME

  findDMRoom(user: User): Rooms | false {
    for (const index in this.roomsList)
      if (this.roomsList[index].name === user.pseudo)
        return this.roomsList[index];
    return false;
  }

  kickUser(user: User) {
    // console.log('kicked ' + user.pseudo);
    this.http
      .patch<User>('/api/rooms/ban/' + this.current_room.id, {
        appuserID: user.id,
      })
      .subscribe({
        next: () => {
          this.wss.emit('kicked', {
            id: user.id,
            roomid: this.current_room.id,
          });
          this.http
            .patch<User>('/api/rooms/unban/' + this.current_room.id, {
              appuserID: user.id,
            })
            .subscribe({
              next: () => {
                // console.log('Kicked user ' + user.pseudo);
                this.wss.emit('kicked', {
                  id: user.id,
                  roomid: this.current_room.id,
                });
              },
              error: (err: any) => {
                // console.log(err);
                this.dialog.open(ErrorPopupComponent, {
                  data: { error: err.error.message },
                });
              },
            });
        },
        error: (err: any) => {
          // console.log(err);
          this.dialog.open(ErrorPopupComponent, {
            data: { error: err.error.message },
          });
        },
      });
    this.ListUserJoinedRoom(this.current_room.id);
  }

  banUser(user: User) {
    // console.log('ban for ' + user.pseudo);
    const statusUser: number = this.searchStatus(user.id);
    const route: string = statusUser !== 6 ? 'ban' : 'unban';
    // console.log('/api/rooms/' + route + '/' + this.current_room.id);
    this.http
      .patch<User>('/api/rooms/' + route + '/' + this.current_room.id, {
        appuserID: user.id,
      })
      .subscribe({
        next: () => {
          // console.log(route + 'ed user ' + user.pseudo);
          //this.wss.emit('update-users');
          if (route === 'ban')
            this.wss.emit('kicked', {
              id: user.id,
              roomid: this.current_room.id,
            });
          else this.wss.emit('update-users');
        },
        error: (err: any) => {
          // console.log(err);
          this.dialog.open(ErrorPopupComponent, {
            data: { error: err.error.message },
          });
        },
      });
    this.ListUserJoinedRoom(this.current_room.id);
  }

  promotionUser(user: User) {
    // console.log('promote for ' + user.pseudo);
    if (this.searchStatus(user.id) === 3)
      this.http
        .patch<User>('/api/rooms/promote/' + this.current_room.id, {
          appuserID: user.id,
        })
        .subscribe({
          next: () => {
            // console.log('Promoted user ' + user.pseudo);
            this.wss.emit('update-users');
          },
          error: (err: any) => {
            // console.log(err);
            this.dialog.open(ErrorPopupComponent, {
              data: { error: err.error.message },
            });
          },
        });
    else if (this.searchStatus(user.id) === 2)
      this.http
        .patch<User>('/api/rooms/demote/' + this.current_room.id, {
          appuserID: user.id,
        })
        .subscribe({
          next: () => {
            // console.log('Demoted user ' + user.pseudo);
            this.wss.emit('update-users');
          },
          error: (err: any) => {
            // console.log(err);
            this.dialog.open(ErrorPopupComponent, {
              data: { error: err.error.message },
            });
          },
        });
    this.ListUserJoinedRoom(this.current_room.id);
  }

  muteUser(user: User) {
    // console.log('mute for ' + user.pseudo);
    const statusUser: number = this.searchStatus(user.id);
    const route: string = statusUser !== 5 ? 'mute' : 'unmute';

    this.http
      .patch<User>('/api/rooms/' + route + '/' + this.current_room.id, {
        appuserID: user.id,
      })
      .subscribe({
        next: () => {
          // console.log(route + ' user ' + user.pseudo);
          this.wss.emit('update-users');
        },
        error: (err: any) => {
          // console.log(err);
          this.dialog.open(ErrorPopupComponent, {
            data: { error: err.error.message },
          });
        },
      });
    this.ListUserJoinedRoom(this.current_room.id);
  }

  changeOwnership(user: User) {
    // console.log('changeowner for ' + user.pseudo);
    if (this.searchStatus(user.id) !== 1) {
      this.http
        .patch<User>('/api/rooms/transferOwnership/' + this.current_room.id, {
          appuserID: user.id,
        })
        .subscribe({
          next: () => {
            // console.log('Owner is now ' + user.pseudo);
            this.wss.emit('update-users');
          },
          error: (err: any) => {
            // console.log(err);
            this.dialog.open(ErrorPopupComponent, {
              data: { error: err.error.message },
            });
          },
        });
      this.ListUserJoinedRoom(this.current_room.id);
    }
  }

  getRoomName(room: Rooms): string {
    if (room.isdm) {
      const nameParts: string[] = room.name.split('-');
      const usersID: number[] = [+nameParts[1], +nameParts[2]];
      const usersDM: number =
        usersID[0] !== this.user.id ? usersID[0] : usersID[1];
      const renameDMName: string | null = this.searchUserNamebyId(usersDM);
      if (renameDMName !== null) return renameDMName;
    }
    return room.name;
  }

  makeRoomsList() {
    this.http.get<Rooms[]>('/api/rooms').subscribe((listedRooms) => {
      this.roomsList = listedRooms;
      for (const crnt in this.roomsList) {
        const channel: Rooms = listedRooms[crnt];
        this.roomsList[crnt].name = this.getRoomName(channel);
        //        this.roomsList.push(channel);
      }
      // console.log(this.roomsList);
    });
  }

  /*
   ** Utils ----------------------------------------------------------------------------------------------------------------------------
   */

  getRoomByID(id: number): Rooms | null {
    for (let room = 0; this.roomsList[room]; ++room) {
      if (this.roomsList[room].id === id) return this.roomsList[room];
    }
    return null;
  }

  searchStatus(id: number): number {
    for (let u = 0; this.channelUsers[u]; u++)
      if (this.channelUsers[u].id === id) {
        for (let a = 0; this.current_room.Access[a]; a++)
          if (this.current_room.Access[a].appuserID === id)
            return this.current_room.Access[a].AuthorizationID;
      }
    // console.log("Search Status");
    // console.log(this.current_room.Access);
    return -1;
  }

  showStatus(id: number): string {
    enum AuthID {
      'Owner' = 1,
      'Admin' = 2,
      'User' = 3,
      'Left' = 4,
      'Mute' = 5,
      'Banned' = 6,
    }
    const status = this.searchStatus(id);
    if (status === -1 || this.current_room.id === -1) return '';
    return ': ' + AuthID[status];
  }

  getUserbyID(userID: number): User | null {
    for (let user = 0; this.usersList[user]; ++user)
      if (this.usersList[user].id === userID) return this.usersList[user];
    return null;
  }

  searchUserNamebyId(id: number): string | null {
    for (let a = 0; this.usersList[a]; ++a)
      if (this.usersList[a].id === id) return this.usersList[a].pseudo;
    return null;
  }

  scrollToBottom(name: string): void {
    try {
      const list = document.getElementsByClassName(name)[0] as HTMLSpanElement;
      list.scrollTop = 0;
    } catch (err) {}
  }

  scrollToBottom2(name: string): void {
    try {
      const list = document.getElementsByClassName(name)[0] as HTMLSpanElement;
      list.scrollTop = list.scrollHeight;
    } catch (err) {}
  }

  getblocked(): void {
    this.http.get<User[]>('api/appusers/me/blocked').subscribe((data) => {
      if (data !== null && data !== undefined) {
        for (const a of data) this.usersblocked.push(a.id);
      }
    });
    // console.log(this.usersblocked);
  }
}
