import { Controller, Get, Headers, Req, UseGuards } from '@nestjs/common';
import { JwtService } from './jwt/jwt.service';
import { api42Guard } from './oauth2/oauth2.guard';

@Controller('auth')
export class AuthController {
  constructor(private jwtService: JwtService) {}

  @Get('login')
  @UseGuards(api42Guard)
  async login(@Req() req) {
    const token = await this.jwtService.login(req.user);
    const responseHTML =
      "<html><head><title>Hello</title></head><body><script>localStorage.setItem('accessToken', '%value%');window.close();</script></body></html>";
    return responseHTML.replace('%value%', token.accessToken);
  }

  @Get('verify')
  verify(@Headers() head) {
    if ('authorization' in head && head.authorization.startsWith('Bearer ')) {
      return this.jwtService.verifyToken(head.authorization.substring(7));
    }
    return { valid: false, isAuthed: false };
  }
}
