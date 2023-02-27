import { ApiProperty, PartialType } from '@nestjs/swagger';
import { IsBase64, IsOptional, IsString, Length } from 'class-validator';
import { CreateAppuserDto } from './create-appuser.dto';

export class UpdateAppuserDto extends PartialType(CreateAppuserDto) {
  @ApiProperty({ required: false })
  @IsString()
  @Length(3)
  @IsOptional()
  pseudo?: string;

  @ApiProperty({ required: false })
  @IsString()
  @IsOptional()
  @IsBase64()
  avatar?: string;
}
