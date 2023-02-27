import { Module } from '@nestjs/common';
import { AppusersModule } from 'src/appusers/appusers.module';
import { GameService } from './game/game.service';
import { SsgGateway } from './socket.gateway';
import { SocketService } from './socket.service';
import { ChatService } from './chat/chat.service';
import { RoomsModule } from 'src/rooms/rooms.module';
import { GamesModule } from 'src/games/games.module';
import { JwtModule } from 'src/auth/jwt/jwt.module';

@Module({
  imports: [JwtModule, AppusersModule, RoomsModule, GamesModule],
  providers: [SsgGateway, GameService, SocketService, ChatService],
})
export class SocketModule {}
