import { Component, Inject } from '@angular/core';
import { MAT_DIALOG_DATA, MatDialogRef } from '@angular/material/dialog';
import { Router } from '@angular/router';

export interface DialogData {
  error: string;
}

@Component({
  selector: 'app-error-join-game',
  templateUrl: './error-join-game.component.html',
  styleUrls: ['./error-join-game.component.css'],
})
export class ErrorJoinGameComponent {
  constructor(
    public dialogRef: MatDialogRef<ErrorJoinGameComponent>,
    private router: Router,
    @Inject(MAT_DIALOG_DATA) public data: { error: string; gameUUID: string },
  ) {}

  return() {
    this.dialogRef.close();
  }

  joinAsSpectator() {
    this.router.navigate(['Game/' + this.data.gameUUID]);
    this.dialogRef.close();
  }
}
