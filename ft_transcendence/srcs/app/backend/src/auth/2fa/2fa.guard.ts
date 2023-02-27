import { CanActivate, ExecutionContext, Injectable } from '@nestjs/common';
import { JwtService } from '../jwt/jwt.service';

@Injectable()
export class Pre2fa implements CanActivate {
  constructor(private jwtService: JwtService) {}

  async canActivate(context: ExecutionContext): Promise<boolean> {
    const req = context.switchToHttp().getRequest();
    const res =
      req.rawHeaders[
        req.rawHeaders.findIndex((headers) => {
          return headers.startsWith('Bearer');
        }, 'Bearer')
      ];
    const user: { valid: boolean; isAuthed: boolean } =
      await this.jwtService.verifyToken(res.substring(7));
    if (user.valid) {
      return true;
    }
    return false;
  }
}
