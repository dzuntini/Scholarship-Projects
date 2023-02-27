import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { FormBuilder, Validators } from '@angular/forms';
import { Router } from '@angular/router';
import { validator } from '../shared/auth.guard';
import { ErrorPopupComponent } from '../error-popup/error-popup.component';
import { MatDialog } from '@angular/material/dialog';

@Component({
  selector: 'app-twofa',
  templateUrl: './twofa.component.html',
  styleUrls: ['./twofa.component.css'],
})
export class TwofaComponent implements OnInit {
  error = '';
  twofa = this.formBuilder.group({
    code: this.formBuilder.control('', [
      Validators.required,
      Validators.maxLength(6),
      Validators.minLength(6),
      Validators.pattern('[0-9]{6}'),
    ]),
  });

  constructor(
    private formBuilder: FormBuilder,
    private http: HttpClient,
    private router: Router,
    private dialog: MatDialog,
  ) {}

  ngOnInit(): void {
    if (localStorage.getItem('accessToken') === null) {
      this.router.navigate(['Login']);
    } else {
      this.http.get<validator>('/api/auth/verify').subscribe((data) => {
        if (data.valid === false) {
          this.router.navigate(['Login']);
        } else if (data.isAuthed === true) {
          this.router.navigate(['Home']);
        }
      });
    }
  }

  authy() {
    if (this.twofa.valid) {
      this.http
        .patch<{ accessToken: string }>('/api/2fa/authenticate', {
          twoFactorAuthenticationCode: this.twofa.value.code,
        })
        .subscribe({
          next: (data) => {
            window.localStorage.setItem('accessToken', data.accessToken);
            this.router.navigate(['Home']);
          },
          error: () => {
            this.dialog.open(ErrorPopupComponent, {
              data: { error: 'Invalid 2FA Code!' },
            });
            this.error = 'Invalid 2FA Code!';
          },
        });
    }
  }
}
