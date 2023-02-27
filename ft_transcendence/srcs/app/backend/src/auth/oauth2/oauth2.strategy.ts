import { PassportStrategy } from '@nestjs/passport';
import { Injectable } from '@nestjs/common';
import { Strategy } from 'passport-oauth2';
import { ConfigService } from '@nestjs/config';
import { oAuth2Service } from './oauth2.service';
import { HttpService } from '@nestjs/axios';
import { firstValueFrom } from 'rxjs';
import { stringify } from 'querystring';

@Injectable()
export class oAuth2Strategy extends PassportStrategy(Strategy, '42api') {
  constructor(
    private authService: oAuth2Service,
    private configService: ConfigService,
    private httpService: HttpService,
  ) {
    super({
      authorizationURL: `${configService.get<string>(
        'api42.authorizationURL',
      )}${stringify({
        client_id: configService.get<string>('api42.uid'),
        redirect_uri: configService.get<string>('api42.callbackURL'),
        response_type: 'code',
      })}`,
      tokenURL: configService.get<string>('api42.tokenURL'),
      clientID: configService.get<string>('api42.uid'),
      clientSecret: configService.get<string>('api42.sec'),
      callbackURL: configService.get<string>('api42.callbackURL'),
    });
  }

  async validate(accessToken: string): Promise<any> {
    const data = await firstValueFrom(
      this.httpService.get('https://api.intra.42.fr/v2/me', {
        headers: { Authorization: `Bearer ${accessToken}` },
      }),
    );
    return this.authService.findUserFrom(data.data.login, data.data.image.link);
  }
}
