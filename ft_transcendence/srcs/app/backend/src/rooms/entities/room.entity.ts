import { ApiProperty } from '@nestjs/swagger';
import { Room as R } from '@prisma/client';

export class Room implements R {
  @ApiProperty()
  id: number;

  @ApiProperty()
  name: string;

  password: string;

  @ApiProperty()
  haspass: boolean;

  @ApiProperty()
  isdm: boolean;

  @ApiProperty()
  visible: boolean;
}
