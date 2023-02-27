import { Module } from '@nestjs/common';
import { RoomsService } from './rooms.service';
import { RoomsController } from './rooms.controller';
import { PrismaModule } from 'src/prisma/prisma.module';
import { AppusersModule } from 'src/appusers/appusers.module';

@Module({
  controllers: [RoomsController],
  providers: [RoomsService],
  imports: [PrismaModule, AppusersModule],
  exports: [RoomsService],
})
export class RoomsModule {}
