import { ApiProperty } from '@nestjs/swagger';
import {
  IsAlphanumeric,
  IsBoolean,
  IsOptional,
  IsString,
  Length,
} from 'class-validator';

export class UpdateRoomDto {
  @ApiProperty({ required: false })
  @IsOptional()
  @IsString()
  @Length(3, 15)
  @IsAlphanumeric()
  name?: string;

  @ApiProperty({ required: false })
  @IsOptional()
  @IsString()
  password?: string;

  @ApiProperty({ required: false })
  @IsOptional()
  @IsBoolean()
  visible?: boolean;
}
