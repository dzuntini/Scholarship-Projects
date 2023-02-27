import { Component, Inject } from '@angular/core';
import { MatDialogRef, MAT_DIALOG_DATA } from '@angular/material/dialog';
import { CreateDialogData } from '../chatroom/chatroom.component';
import { FormBuilder, Validators } from '@angular/forms';

@Component({
  selector: 'app-chatroom-create-room',
  templateUrl: './chatroom-join-room.component.html',
  styleUrls: ['./chatroom-join-room.component.css'],
})
export class ChatRoomJoinRoom {
  chatJoinRoom = this.formBuilder.group({
    name: this.formBuilder.control('', [
      Validators.required,
      Validators.pattern('[a-zA-Z0-9]*'),
    ]),
    password: this.formBuilder.control('', []),
  });

  constructor(
    public dialogRef: MatDialogRef<ChatRoomJoinRoom>,
    @Inject(MAT_DIALOG_DATA) public data: CreateDialogData,
    private formBuilder: FormBuilder,
  ) {}

  onNoClick(): void {
    this.dialogRef.close();
  }

  _return() {
    if (this.chatJoinRoom.valid) {
      this.data.name = this.chatJoinRoom.value.name as string;
      this.data.password = this.chatJoinRoom.value.password as
        | string
        | undefined;
      // console.log(this.data);
      this.dialogRef.close(this.data);
    }
  }
}
