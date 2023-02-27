import { ApiProperty } from '@nestjs/swagger';
import { IsNotEmpty, IsNumber } from 'class-validator';

export class CreateDMDto {
  @IsNotEmpty()
  @IsNumber()
  @ApiProperty()
  otherId;
}
