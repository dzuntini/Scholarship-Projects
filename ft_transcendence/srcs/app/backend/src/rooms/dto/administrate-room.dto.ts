import { ApiProperty } from '@nestjs/swagger';
import { IsNotEmpty, IsNumber } from 'class-validator';

export class AdministrateRoomDto {
  @ApiProperty()
  @IsNumber()
  @IsNotEmpty()
  appuserID: number;
}
