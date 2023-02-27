import { ApiProperty } from '@nestjs/swagger';
import { IsOptional, IsString } from 'class-validator';

export class JoinRoomDto {
  @ApiProperty()
  @IsString()
  @IsOptional()
  password?: string;
}
