import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { authenticator } from 'otplib';
import { AppusersService } from 'src/appusers/appusers.service';
import { Appuser } from 'src/appusers/entities/appuser.entity';
import { toFileStream } from 'qrcode';

@Injectable()
export class TwoFactorAuthenticationService {
  constructor(
    private readonly usersService: AppusersService,
    private readonly configService: ConfigService,
  ) {}

  async generateTwoFactorAuthenticationSecret(id: number) {
    const user = await this.usersService.findOneByIDNoHide(id);
    if (user.twoFactorAuthSecret !== '') {
      const secret = user.twoFactorAuthSecret;
      const otpauthUrl = authenticator.keyuri(
        user.login,
        this.configService.get('2fa.name'),
        secret,
      );
      return {
        secret,
        otpauthUrl,
      };
    }
    const secret = authenticator.generateSecret();
    const otpauthUrl = authenticator.keyuri(
      user.login,
      this.configService.get('2fa.name'),
      secret,
    );
    await this.usersService.setTwoFactorAuthenticationSecret(secret, user.id);
    return {
      secret,
      otpauthUrl,
    };
  }

  async pipeQrCodeStream(stream: Response, otpauthUrl: string) {
    return toFileStream(stream, otpauthUrl);
  }

  isTwoFactorAuthenticationCodeValid(
    twoFactorAuthenticationCode: string,
    user: Appuser,
  ) {
    return authenticator.verify({
      token: twoFactorAuthenticationCode,
      secret: user.twoFactorAuthSecret,
    });
  }
}
