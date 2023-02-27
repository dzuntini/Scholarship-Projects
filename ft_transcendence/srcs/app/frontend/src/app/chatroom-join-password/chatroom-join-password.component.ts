import { Component, Inject } from '@angular/core';
import { FormBuilder, Validators } from '@angular/forms';
import { MAT_DIALOG_DATA, MatDialogRef } from '@angular/material/dialog';
import { CreateDialogData } from '../chatroom/chatroom.component';

@Component({
  selector: 'app-chatroom-join-password',
  templateUrl: './chatroom-join-password.component.html',
  styleUrls: ['./chatroom-join-password.component.css'],
})
export class ChatroomJoinPasswordComponent {
  joinpassword = this.formBuilder.group({
    password: this.formBuilder.control('', [Validators.required]),
  });

  constructor(
    public dialogRef: MatDialogRef<ChatroomJoinPasswordComponent>,
    @Inject(MAT_DIALOG_DATA) public data: CreateDialogData,
    private formBuilder: FormBuilder,
  ) {}

  onNoClick(): void {
    this.dialogRef.close();
  }

  _return() {
    if (this.joinpassword.valid) {
      this.data.password = this.joinpassword.value.password as string;
      // console.log(this.data);
      this.dialogRef.close(this.data);
    }
  }
}
