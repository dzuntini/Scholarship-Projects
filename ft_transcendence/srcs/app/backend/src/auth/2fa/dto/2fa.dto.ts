import { ApiProperty } from '@nestjs/swagger';
import { IsNotEmpty, IsString, Length } from 'class-validator';

export class TwoFactorAuthenticate {
  @ApiProperty()
  @IsString()
  @IsNotEmpty()
  @Length(6, 6)
  twoFactorAuthenticationCode: string;
}
