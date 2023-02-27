import { ApiProperty } from '@nestjs/swagger';
import {
  IsAlphanumeric,
  IsBoolean,
  IsNotEmpty,
  IsOptional,
  IsString,
  Length,
} from 'class-validator';

export class CreateRoomDto {
  @IsNotEmpty()
  @IsString()
  @IsAlphanumeric()
  @ApiProperty()
  @Length(3, 15)
  name: string;

  @IsString()
  @IsOptional()
  @ApiProperty({ required: false })
  password?: string;

  @IsBoolean()
  @IsOptional()
  @ApiProperty({ required: false })
  visible?: boolean;
}
