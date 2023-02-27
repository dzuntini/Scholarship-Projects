import { Module } from '@nestjs/common';
import { GamesService } from './games.service';
import { GamesController } from './games.controller';
import { PrismaModule } from 'src/prisma/prisma.module';
import { AppusersModule } from 'src/appusers/appusers.module';

@Module({
  controllers: [GamesController],
  providers: [GamesService],
  imports: [AppusersModule, PrismaModule],
  exports: [GamesService],
})
export class GamesModule {}
