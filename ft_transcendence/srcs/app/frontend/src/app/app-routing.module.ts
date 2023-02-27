import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { HomeComponent } from './home/home.component';
import { LoginComponent } from './login/login.component';
import { ProfileComponent } from './profile/profile.component';
import { GameComponent } from './game/game.component';
import { ChatRoomComponent } from './chatroom/chatroom.component';
import { RankingComponent } from './ranking/ranking.component';
import { LivegamesComponent } from './livegames/livegames.component';
import { Error404Component } from './error404/error404.component';
import { FrontAuthGuard } from './shared/auth.guard';
import { TwofaComponent } from './twofa/twofa.component';

const routes: Routes = [
  { path: 'Login', component: LoginComponent },
  { path: '2FA', component: TwofaComponent },
  { path: 'Home', component: HomeComponent, canActivate: [FrontAuthGuard] },
  { path: '', redirectTo: '//Home', pathMatch: 'full' },
  {
    path: 'Profile/:id',
    component: ProfileComponent,
    canActivate: [FrontAuthGuard],
  },
  { path: 'Chat', component: ChatRoomComponent, canActivate: [FrontAuthGuard] },
  { path: 'Game/:id', component: GameComponent, canActivate: [FrontAuthGuard] },
  {
    path: 'Ranking',
    component: RankingComponent,
    canActivate: [FrontAuthGuard],
  },
  {
    path: 'LiveGames',
    component: LivegamesComponent,
    canActivate: [FrontAuthGuard],
  },
  { path: '**', pathMatch: 'full', component: Error404Component },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule],
})
export class AppRoutingModule {}
