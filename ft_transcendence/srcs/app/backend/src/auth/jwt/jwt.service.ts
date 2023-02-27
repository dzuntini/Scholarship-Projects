import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { JwtService as NestJwtService } from '@nestjs/jwt';
import { AppusersService } from 'src/appusers/appusers.service';
import { JwtPayload } from './jwt.strategy';

@Injectable()
export class JwtService {
  constructor(
    private jwtService: NestJwtService,
    private configService: ConfigService,
    private appusersService: AppusersService,
  ) {}

  async login(user: any) {
    const payload: JwtPayload = {
      username: user.login,
      sub: user.id,
      isAuthenticated: !(await this.appusersService.findOneByID(user.id))
        .twoFactorAuthEnabled,
    };
    return {
      accessToken: this.jwtService.sign(payload, {
        secret: this.configService.get<string>('jwt.secret'),
      }),
    };
  }

  async verifyToken(
    token: string,
  ): Promise<{ valid: boolean; isAuthed: boolean }> {
    try {
      this.jwtService.verify(token, {
        secret: this.configService.get<string>('jwt.secret'),
      });
    } catch (error) {
      return { valid: false, isAuthed: false };
    }
    const decodedToken = this.decodeToken(token);
    const user = await this.appusersService.findOneByID(decodedToken.sub);
    if (!user) {
      return { valid: false, isAuthed: false };
    }
    if (user.twoFactorAuthEnabled) {
      if (decodedToken.isAuthenticated) {
        return { valid: true, isAuthed: true };
      } else {
        return { valid: true, isAuthed: false };
      }
    } else {
      return { valid: true, isAuthed: true };
    }
  }

  decodeToken(token: string): { [key: string]: any } {
    return this.jwtService.decode(token, { json: true }) as {
      [key: string]: any;
    };
  }
}
