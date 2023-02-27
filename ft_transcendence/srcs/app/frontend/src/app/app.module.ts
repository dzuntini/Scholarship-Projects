// Angular Imports
import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { HttpClientModule, HTTP_INTERCEPTORS } from '@angular/common/http';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';

// Material UI Imports
import { MatAutocompleteModule } from '@angular/material/autocomplete';
import { MatBadgeModule } from '@angular/material/badge';
import { MatBottomSheetModule } from '@angular/material/bottom-sheet';
import { MatButtonModule } from '@angular/material/button';
import { MatButtonToggleModule } from '@angular/material/button-toggle';
import { MatCardModule } from '@angular/material/card';
import { MatCheckboxModule } from '@angular/material/checkbox';
import { MatChipsModule } from '@angular/material/chips';
import { MatStepperModule } from '@angular/material/stepper';
import { MatDatepickerModule } from '@angular/material/datepicker';
import { MatDialogModule } from '@angular/material/dialog';
import { MatDividerModule } from '@angular/material/divider';
import { MatExpansionModule } from '@angular/material/expansion';
import { MatGridListModule } from '@angular/material/grid-list';
import { MatIconModule } from '@angular/material/icon';
import { MatInputModule } from '@angular/material/input';
import { MatListModule } from '@angular/material/list';
import { MatMenuModule } from '@angular/material/menu';
import { MatNativeDateModule, MatRippleModule } from '@angular/material/core';
import { MatPaginatorModule } from '@angular/material/paginator';
import { MatProgressBarModule } from '@angular/material/progress-bar';
import { MatProgressSpinnerModule } from '@angular/material/progress-spinner';
import { MatRadioModule } from '@angular/material/radio';
import { MatSelectModule } from '@angular/material/select';
import { MatSidenavModule } from '@angular/material/sidenav';
import { MatSliderModule } from '@angular/material/slider';
import { MatSlideToggleModule } from '@angular/material/slide-toggle';
import { MatSnackBarModule } from '@angular/material/snack-bar';
import { MatSortModule } from '@angular/material/sort';
import { MatTableModule } from '@angular/material/table';
import { MatTabsModule } from '@angular/material/tabs';
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatTooltipModule } from '@angular/material/tooltip';
import { MatTreeModule } from '@angular/material/tree';

// Material CDK Imports
import { ScrollingModule } from '@angular/cdk/scrolling';

// Home Screen
import { HomeComponent } from './home/home.component';

// Login Screen
import { LoginComponent } from './login/login.component';
import { TwofaComponent } from './twofa/twofa.component';

// Profile Screen
import { ProfileComponent } from './profile/profile.component';
import { ProfileFriendlistComponent } from './profile-friendlist/profile-friendlist.component';
import { ProfileGamesComponent } from './profile-games/profile-games.component';

// Game Screen
import { GameComponent } from './game/game.component';

// Live Games Screen
import { LivegamesComponent } from './livegames/livegames.component';

// Ranking Screen
import { RankingComponent } from './ranking/ranking.component';

// Chat Room
import { ChatRoomComponent } from './chatroom/chatroom.component';
import { ChatRoomCreateRoom } from './chatroom-create-room/chatroom-create-room.component';
import { ChatRoomDeleteRoom } from './chatroom-delete-room/chatroom-delete-room.component';
import { ChatRoomJoinRoom } from './chatroom-join-room/chatroom-join-room.component';
import { ChatRoomModifyRoom } from './chatroom-modify-room/chatroom-modify-room.component';
import { ChatroomJoinPasswordComponent } from './chatroom-join-password/chatroom-join-password.component';

// Multi-Use
import { NavigationBarComponent } from './navigation-bar/navigation-bar.component';
import { SocketIoConfig, SocketIoModule } from 'ngx-socket-io';
import { AuthInterceptor } from './shared/authconfig.interceptor';

// Error
import { Error404Component } from './error404/error404.component';
import { ErrorPopupComponent } from './error-popup/error-popup.component';
import { EndGameComponent } from './end-game/end-game.component';
import { ErrorJoinGameComponent } from './error-join-game/error-join-game.component';
import { environment } from 'src/environments/environment';

const config: SocketIoConfig = {
  url: 'http://' + environment.ws_host + '/socket.io',
  options: {},
};

@NgModule({
  declarations: [
    AppComponent,
    GameComponent,
    ChatRoomComponent,
    ChatRoomCreateRoom,
    ChatRoomDeleteRoom,
    ChatRoomJoinRoom,
    ChatRoomModifyRoom,
    ProfileComponent,
    ProfileFriendlistComponent,
    RankingComponent,
    HomeComponent,
    LoginComponent,
    LivegamesComponent,
    NavigationBarComponent,
    Error404Component,
    TwofaComponent,
    ProfileGamesComponent,
    ErrorPopupComponent,
    ChatroomJoinPasswordComponent,
    EndGameComponent,
    ErrorJoinGameComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    FormsModule,
    ReactiveFormsModule,
    MatAutocompleteModule,
    MatBadgeModule,
    MatBottomSheetModule,
    MatButtonModule,
    MatButtonToggleModule,
    MatCardModule,
    MatCheckboxModule,
    MatChipsModule,
    MatStepperModule,
    MatDatepickerModule,
    MatDialogModule,
    MatDividerModule,
    MatExpansionModule,
    MatGridListModule,
    MatIconModule,
    MatInputModule,
    MatListModule,
    MatMenuModule,
    MatNativeDateModule,
    MatRippleModule,
    MatPaginatorModule,
    MatProgressBarModule,
    MatProgressSpinnerModule,
    MatRadioModule,
    MatSelectModule,
    MatSidenavModule,
    MatSliderModule,
    MatSlideToggleModule,
    MatSnackBarModule,
    MatSortModule,
    MatTableModule,
    MatTabsModule,
    MatToolbarModule,
    MatTooltipModule,
    MatTreeModule,
    ScrollingModule,
    BrowserAnimationsModule,
    ReactiveFormsModule,
    SocketIoModule.forRoot(config),
  ],
  providers: [
    {
      provide: HTTP_INTERCEPTORS,
      useClass: AuthInterceptor,
      multi: true,
    },
  ],
  bootstrap: [AppComponent],
})
export class AppModule {}
