import { Component, Inject } from '@angular/core';
import { MAT_DIALOG_DATA, MatDialogRef } from '@angular/material/dialog';
import { endInfos } from '../shared/web-sockets.service';

@Component({
  selector: 'app-end-game',
  templateUrl: './end-game.component.html',
  styleUrls: ['./end-game.component.css'],
})
export class EndGameComponent {
  constructor(
    public dialogRef: MatDialogRef<EndGameComponent>,
    @Inject(MAT_DIALOG_DATA) public data: endInfos,
  ) {}

  returnHome() {
    this.dialogRef.close();
  }
}
