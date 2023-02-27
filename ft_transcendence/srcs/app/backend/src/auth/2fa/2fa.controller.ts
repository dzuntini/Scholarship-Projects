import { JwtService as NestJwtService } from '@nestjs/jwt';
import { JwtAuthGuard } from '../jwt/jwt.guard';
import { JwtService } from '../jwt/jwt.service';
import { JwtPayload } from '../jwt/jwt.strategy';
import {
  Body,
  ClassSerializerInterceptor,
  Controller,
  Get,
  Patch,
  Req,
  Res,
  UnauthorizedException,
  UseGuards,
  UseInterceptors,
} from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { ApiTags } from '@nestjs/swagger';
import { AppusersService } from 'src/appusers/appusers.service';
import { Pre2fa } from './2fa.guard';
import { TwoFactorAuthenticationService } from './2fa.service';
import { TwoFactorAuthenticate } from './dto/2fa.dto';

@Controller('2fa')
@UseInterceptors(ClassSerializerInterceptor)
@ApiTags('2fa')
export class TwoFactorAuthenticationController {
  constructor(
    private readonly twoFactorAuthenticationService: TwoFactorAuthenticationService,
    private readonly appusersService: AppusersService,
    private readonly jwtService: NestJwtService,
    private readonly jwtServ: JwtService,
    private readonly configService: ConfigService,
  ) {}

  @Patch('toggle')
  @UseGuards(JwtAuthGuard)
  async turnOnTwoFactorAuthentication(
    @Req() request,
    @Body() twoFactorAuthentication: TwoFactorAuthenticate,
  ) {
    const user = await this.appusersService.findOneByIDNoHide(
      request.user.userId,
    );
    if (!user) {
      throw new UnauthorizedException('User invalid!');
    }
    const isCodeValid =
      this.twoFactorAuthenticationService.isTwoFactorAuthenticationCodeValid(
        twoFactorAuthentication.twoFactorAuthenticationCode,
        user,
      );
    if (!isCodeValid) {
      throw new UnauthorizedException('Wrong authentication code');
    }
    return this.appusersService.toggleTwoFactorAuthentication(
      request.user.userId,
    );
  }

  @Patch('authenticate')
  @UseGuards(Pre2fa)
  async authenticate(
    @Req() request,
    @Body() twoFactorAuthentication: TwoFactorAuthenticate,
  ) {
    const res =
      request.rawHeaders[
        request.rawHeaders.findIndex((headers) => {
          return headers.startsWith('Bearer');
        }, 'Bearer')
      ];
    const userID = this.jwtServ.decodeToken(res.substring(7));
    const user = await this.appusersService.findOneByIDNoHide(userID.sub);
    if (user) {
      if (user.twoFactorAuthEnabled === false) {
        throw new UnauthorizedException('User does not have 2fa enabled');
      }
      const isCodeValid =
        this.twoFactorAuthenticationService.isTwoFactorAuthenticationCodeValid(
          twoFactorAuthentication.twoFactorAuthenticationCode,
          user,
        );
      if (!isCodeValid) {
        throw new UnauthorizedException('Wrong authentication code');
      }
      const payload: JwtPayload = {
        username: user.login,
        sub: user.id,
        isAuthenticated: true,
      };
      return {
        accessToken: this.jwtService.sign(payload, {
          secret: this.configService.get<string>('jwt.secret'),
        }),
      };
    }
  }

  @Get('generate')
  @UseGuards(JwtAuthGuard)
  async register(@Res() response: Response, @Req() payload) {
    const { otpauthUrl } =
      await this.twoFactorAuthenticationService.generateTwoFactorAuthenticationSecret(
        payload.user.userId,
      );

    return this.twoFactorAuthenticationService.pipeQrCodeStream(
      response,
      otpauthUrl,
    );
  }
}
