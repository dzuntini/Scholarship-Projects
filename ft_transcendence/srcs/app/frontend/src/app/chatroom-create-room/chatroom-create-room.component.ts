import { Component, Inject } from '@angular/core';
import { MatDialogRef, MAT_DIALOG_DATA } from '@angular/material/dialog';
import { CreateDialogData } from '../chatroom/chatroom.component';
import { FormBuilder, Validators } from '@angular/forms';

@Component({
  selector: 'app-chatroom-create-room',
  templateUrl: './chatroom-create-room.component.html',
  styleUrls: ['./chatroom-create-room.component.css'],
})
export class ChatRoomCreateRoom {
  chatCreateRoom = this.formBuilder.group({
    name: this.formBuilder.control('', [
      Validators.required,
      Validators.pattern('[a-zA-Z0-9]*'),
      Validators.maxLength(15),
      Validators.minLength(3),
    ]),
    password: this.formBuilder.control('', []),
    visible: true,
  });

  constructor(
    public dialogRef: MatDialogRef<ChatRoomCreateRoom>,
    @Inject(MAT_DIALOG_DATA) public data: CreateDialogData,
    private formBuilder: FormBuilder,
  ) {}

  onNoClick(): void {
    this.dialogRef.close();
  }

  _return() {
    if (this.chatCreateRoom.valid) {
      this.data.name = this.chatCreateRoom.value.name as string;
      this.data.password = this.chatCreateRoom.value.password as
        | string
        | undefined;
      if (
        this.chatCreateRoom.value.visible === undefined ||
        this.chatCreateRoom.value.visible === null
      ) {
        this.data.visible = false;
      }
      this.data.visible = this.chatCreateRoom.value.visible as boolean;
      // console.log(this.data);
      this.dialogRef.close(this.data);
    }
  }
}
