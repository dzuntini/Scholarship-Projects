import { forwardRef, Module } from '@nestjs/common';
import { ConfigModule, ConfigService } from '@nestjs/config';
import {
  JwtModule as JwtNestModule,
  JwtService as JwtNestService,
} from '@nestjs/jwt';
import { AppusersModule } from 'src/appusers/appusers.module';
import { JwtStrategy } from './jwt.strategy';
import { JwtService } from './jwt.service';

@Module({
  imports: [
    forwardRef(() => AppusersModule),
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
  providers: [JwtStrategy, JwtNestService, JwtService],
  exports: [JwtModule, JwtNestService, JwtService],
})
export class JwtModule {}
