import { ApiProperty } from '@nestjs/swagger';
import { APPUser } from '@prisma/client';

export class Appuser implements APPUser {
  @ApiProperty()
  id: number;

  @ApiProperty()
  login: string;

  @ApiProperty()
  pseudo: string;

  @ApiProperty()
  avatar: string;

  twoFactorAuthSecret: string;

  twoFactorAuthEnabled: boolean;

  @ApiProperty()
  elo: number;

  @ApiProperty()
  nb_played_game: number;

  @ApiProperty()
  nb_defeat: number;

  @ApiProperty()
  nb_victory: number;
}
