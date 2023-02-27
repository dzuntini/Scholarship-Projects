import { HttpClient } from '@angular/common/http';
import { Component, Inject } from '@angular/core';
import { MatDialogRef, MAT_DIALOG_DATA } from '@angular/material/dialog';
import { DelDialogData } from '../chatroom/chatroom.component';
import { WebSocketsService } from '../shared/web-sockets.service';

@Component({
  selector: 'app-chatroom-delete-room',
  templateUrl: './chatroom-delete-room.component.html',
  styleUrls: ['./chatroom-delete-room.component.css'],
})
export class ChatRoomDeleteRoom {
  constructor(
    private http: HttpClient,
    private wss: WebSocketsService,
    public dialogRef: MatDialogRef<ChatRoomDeleteRoom>,
    @Inject(MAT_DIALOG_DATA) public data: DelDialogData,
  ) {
    // console.log(data);
  }

  deleteRoom() {
    // console.log(this.data.id);
    this.http.delete('api/rooms/' + this.data.id).subscribe(); //(result) => // console.log(result));
    this.wss.emit('chat-del-room', { id: this.data.id, name: this.data.room });
    this.dialogRef.close();
  }

  onNoClick(): void {
    this.dialogRef.close();
  }
}
