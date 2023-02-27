import { ExtractJwt, Strategy } from 'passport-jwt';
import { PassportStrategy } from '@nestjs/passport';
import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { AppusersService } from 'src/appusers/appusers.service';

export type JwtPayload = {
  sub: number;
  isAuthenticated: boolean;
  username: string;
};

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy) {
  constructor(
    private configService: ConfigService,
    private appusersService: AppusersService,
  ) {
    super({
      jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
      ignoreExpiration: false,
      secretOrKey: configService.get<string>('jwt.secret'),
    });
  }

  async validate(payload: JwtPayload) {
    const user = await this.appusersService.findOneByID(payload.sub);
    if (user === null) {
      return {
        userId: payload.sub,
        username: payload.username,
        validated: false,
      };
    }
    if (!user.twoFactorAuthEnabled) {
      return {
        userId: payload.sub,
        username: payload.username,
        validated: true,
      };
    } else if (payload.isAuthenticated) {
      return {
        userId: payload.sub,
        username: payload.username,
        validated: true,
      };
    } else if (!payload.isAuthenticated) {
      return {
        userId: payload.sub,
        username: payload.username,
        validated: false,
      };
    }
  }
}
