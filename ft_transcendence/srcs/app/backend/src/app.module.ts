import { Module } from '@nestjs/common';
import { PrismaModule } from './prisma/prisma.module';
import { GamesModule } from './games/games.module';
import { AppusersModule } from './appusers/appusers.module';
import { RoomsModule } from './rooms/rooms.module';
import { ConfigModule } from '@nestjs/config';
import { JwtModule } from './auth/jwt/jwt.module';
import configuration from './configuration/configuration';
import api42Config from './configuration/api42.config';
import databaseConfig from './configuration/database.config';
import jwtConfig from './configuration/jwt.config';
import twofaConfig from './configuration/2fa.config';
import { AuthModule } from './auth/auth.module';
import { SocketModule } from './sockets/socket.module';
import { join } from 'path';
import { ServeStaticModule } from '@nestjs/serve-static';

@Module({
  imports: [
    PrismaModule,
    AuthModule,
    ConfigModule.forRoot({
      isGlobal: true,
      ignoreEnvFile: true,
      load: [
        configuration,
        api42Config,
        databaseConfig,
        jwtConfig,
        twofaConfig,
      ],
      cache: true,
    }),
    ServeStaticModule.forRoot({
      rootPath: join(__dirname, '..', '..', 'frontend', 'dist', 'frontend'),
    }),
    JwtModule,
    AppusersModule,
    GamesModule,
    SocketModule,
    RoomsModule,
  ],
})
export class AppModule {}
