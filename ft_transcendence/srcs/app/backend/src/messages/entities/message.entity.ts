import { ApiProperty } from '@nestjs/swagger';
import { Message as M } from '@prisma/client';

export class Message implements M {
  @ApiProperty()
  id: number;

  @ApiProperty()
  content: string;

  @ApiProperty()
  timestamp: Date;

  @ApiProperty()
  roomID: number;

  @ApiProperty()
  appuserID: number;
}
