import { Module } from '@nestjs/common';
import { JwtService as NestJwtService } from '@nestjs/jwt';
import { AppusersModule } from 'src/appusers/appusers.module';
import { JwtModule } from '../jwt/jwt.module';
import { JwtService } from '../jwt/jwt.service';
import { TwoFactorAuthenticationController } from './2fa.controller';
import { Pre2fa } from './2fa.guard';
import { TwoFactorAuthenticationService } from './2fa.service';

@Module({
  imports: [AppusersModule, JwtModule],
  providers: [
    TwoFactorAuthenticationService,
    NestJwtService,
    Pre2fa,
    JwtService,
  ],
  controllers: [TwoFactorAuthenticationController],
  exports: [TwoFactorAuthenticationModule, TwoFactorAuthenticationService],
})
export class TwoFactorAuthenticationModule {}
