import { ApiProperty } from '@nestjs/swagger';
import { IsBoolean, IsNumber } from 'class-validator';

export class CreateGameDto {
  @ApiProperty({ required: true })
  @IsBoolean()
  ranked: boolean;

  @ApiProperty({ required: true })
  @IsNumber()
  p1_score: number;

  @ApiProperty({ required: true })
  @IsNumber()
  p2_score: number;
}
