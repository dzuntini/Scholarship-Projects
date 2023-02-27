import { HttpModule } from '@nestjs/axios';
import { Module } from '@nestjs/common';
import { AppusersModule } from 'src/appusers/appusers.module';
import { PrismaModule } from 'src/prisma/prisma.module';
import { oAuth2Service } from './oauth2.service';
import { oAuth2Strategy } from './oauth2.strategy';

@Module({
  imports: [HttpModule, AppusersModule, PrismaModule],
  providers: [oAuth2Strategy, oAuth2Service],
  exports: [OAuth2Module],
})
export class OAuth2Module {}
