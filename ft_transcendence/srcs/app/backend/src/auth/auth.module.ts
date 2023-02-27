import { Module } from '@nestjs/common';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { JwtModule as JwtNestModule } from '@nestjs/jwt';
import { AppusersModule } from 'src/appusers/appusers.module';
import { TwoFactorAuthenticationModule } from './2fa/2fa.module';
import { AuthController } from './auth.controler';
import { JwtModule } from './jwt/jwt.module';
import { JwtService } from './jwt/jwt.service';
import { OAuth2Module } from './oauth2/oauth2.module';

@Module({
  controllers: [AuthController],
  providers: [JwtService],
  imports: [
    JwtModule,
    AppusersModule,
    OAuth2Module,
    TwoFactorAuthenticationModule,
    JwtNestModule.registerAsync({
      imports: [ConfigModule],
      inject: [ConfigService],
      useFactory: async (configService: ConfigService) => ({
        secret: configService.get<string>('jwt.secret'),
        signOptions: {
          expiresIn: configService.get<string>('jwt.expiresIn'),
        },
      }),
    }),
  ],
  exports: [AuthModule, JwtModule, OAuth2Module, TwoFactorAuthenticationModule],
})
export class AuthModule {}
