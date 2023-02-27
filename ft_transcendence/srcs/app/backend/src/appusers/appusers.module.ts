import { Module } from '@nestjs/common';
import { AppusersService } from './appusers.service';
import { AppusersController } from './appusers.controller';
import { PrismaModule } from 'src/prisma/prisma.module';
import { JwtModule } from 'src/auth/jwt/jwt.module';

@Module({
  controllers: [AppusersController],
  providers: [AppusersService],
  imports: [PrismaModule, JwtModule],
  exports: [AppusersService],
})
export class AppusersModule {}
