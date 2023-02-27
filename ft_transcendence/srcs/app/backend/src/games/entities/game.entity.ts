import { ApiProperty } from '@nestjs/swagger';
import { Game as G } from '@prisma/client';

export class Game implements G {
  @ApiProperty()
  id: number;

  @ApiProperty()
  ranked: boolean;

  @ApiProperty()
  timestamp: Date;

  @ApiProperty()
  p1_score: number;

  @ApiProperty()
  p2_score: number;

  @ApiProperty()
  statusID: number;
}
