import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import {
  ActivatedRouteSnapshot,
  RouterStateSnapshot,
  CanActivate,
  Router,
} from '@angular/router';

export interface validator {
  valid: boolean;
  isAuthed: boolean;
}

@Injectable({
  providedIn: 'root',
})
export class FrontAuthGuard implements CanActivate {
  constructor(public router: Router, public http: HttpClient) {}

  canActivate(
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    next: ActivatedRouteSnapshot,
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    state: RouterStateSnapshot,
  ): Promise<boolean> | boolean {
    if (localStorage.getItem('accessToken') === null) {
      this.router.navigate(['Login']);
    }
    this.http.get<validator>('/api/auth/verify').subscribe({
      next: (data) => {
        if (data.valid === false) {
          this.router.navigate(['Login']);
        } else if (data.isAuthed === false) {
          this.router.navigate(['2FA']);
        }
      },
      error: () => {
        this.router.navigate(['Login']);
      },
    });
    return true;
  }
}
