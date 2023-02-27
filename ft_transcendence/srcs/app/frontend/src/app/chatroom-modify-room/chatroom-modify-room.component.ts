import { Component, Inject } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { MatDialogRef, MAT_DIALOG_DATA } from '@angular/material/dialog';
import { ModDialogData, Rooms } from '../chatroom/chatroom.component';
import { WebSocketsService } from '../shared/web-sockets.service';
import { FormBuilder, Validators } from '@angular/forms';

@Component({
  selector: 'app-chatroom-modify-room',
  templateUrl: './chatroom-modify-room.component.html',
  styleUrls: ['./chatroom-modify-room.component.css'],
})
export class ChatRoomModifyRoom {
  public a: string = this.data.room;
  public pass: string = this.data.password;

  chatModifyRoom = this.formBuilder.group({
    name: this.formBuilder.control(this.data.room, [
      Validators.pattern('[a-zA-Z0-9]*'),
      Validators.minLength(3),
      Validators.maxLength(15),
    ]),
    password: this.formBuilder.control('', []),
    visible: this.data.visible,
  });

  constructor(
    private http: HttpClient,
    private wss: WebSocketsService,
    public dialogRef: MatDialogRef<ChatRoomModifyRoom>,
    @Inject(MAT_DIALOG_DATA) public data: ModDialogData,
    private formBuilder: FormBuilder,
  ) {}

  modifyRoom() {
    // console.log('Avant le patch' + this.data);
    if (this.chatModifyRoom.valid) {
      if (this.chatModifyRoom.value.name === '') {
        this.chatModifyRoom.value.name = undefined;
      }
      this.http
        .patch<Rooms>('api/rooms/' + this.data.id, {
          name: this.chatModifyRoom.value.name as string,
          password: this.chatModifyRoom.value.password as string,
          visible: this.chatModifyRoom.value.visible as boolean,
        })
        .subscribe({
          next: (a: Rooms) => {
            // console.log('Ici' + a);
            this.wss.emit('chat-modify-room', {
              id: this.data.id,
              name: this.data.room,
            });

            this.dialogRef.close();
          },
          error: () => {
            this.data.id = -1;

            this.dialogRef.close();
          },
        });
    }
  }

  onNoClick(): void {
    this.dialogRef.close();
  }

  _return() {
    this.dialogRef.close();
  }
}
