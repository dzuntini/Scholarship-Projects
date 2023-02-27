import { JwtAuthGuard } from 'src/auth/jwt/jwt.guard';
import {
  Controller,
  Get,
  Post,
  Body,
  Patch,
  Param,
  Delete,
  UseGuards,
  Req,
  BadRequestException,
} from '@nestjs/common';
import { ApiCreatedResponse, ApiOkResponse, ApiTags } from '@nestjs/swagger';
import { RoomsService } from './rooms.service';
import { CreateRoomDto } from './dto/create-room.dto';
import { UpdateRoomDto } from './dto/update-room.dto';
import { Room } from './entities/room.entity';
import { JoinRoomDto } from './dto/join-room.dto';
import { AdministrateRoomDto } from './dto/administrate-room.dto';
import { Appuser } from 'src/appusers/entities/appuser.entity';
import { Message } from 'src/messages/entities/message.entity';
import { CreateDMDto } from './dto/create-directmessage.dto';

export class findNameReturnType {
  id: number;
}

@Controller('rooms')
@ApiTags('Rooms')
@UseGuards(JwtAuthGuard)
export class RoomsController {
  constructor(private readonly roomsService: RoomsService) {}

  @Post()
  @ApiCreatedResponse({ type: Room })
  create(@Body() createRoomDto: CreateRoomDto, @Req() payload: any) {
    return this.roomsService.create(createRoomDto, payload.user);
  }

  @Post('createDM')
  @ApiCreatedResponse({ type: Room })
  createDM(@Body() data: CreateDMDto, @Req() payload: any) {
    return this.roomsService.createDM(payload.user.userId, data.otherId);
  }

  @Get()
  @ApiOkResponse({ type: Room, isArray: true })
  findAll(@Req() payload: any) {
    return this.roomsService.findAll(payload.user.userId);
  }

  @Get(':id')
  @ApiOkResponse({ type: Room })
  findOne(@Param('id') id: string, @Req() payload: any) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.findOne(+id, payload.user.userId);
  }

  @Get('byName/:name')
  @ApiOkResponse({ type: findNameReturnType })
  // eslint-disable-next-line @typescript-eslint/no-unused-vars
  findOneByName(@Param('name') name: string, @Req() _payload: any) {
    return this.roomsService.findOneByName(name);
  }

  @Get('members/:id')
  @ApiOkResponse({ type: Appuser, isArray: true })
  getUsers(@Param('id') id: string, @Req() payload: any) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.getMembersOfRoom(+id, payload.user.userId);
  }

  @Get('messages/:id')
  @ApiOkResponse({ type: Message, isArray: true })
  getMessages(@Param('id') id: string, @Req() payload: any) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.getMessagesOfRoom(+id, payload.user.userId);
  }

  @Patch(':id')
  @ApiOkResponse({ type: Room })
  update(
    @Param('id') id: string,
    @Body() updateRoomDto: UpdateRoomDto,
    @Req() payload: any,
  ) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.update(+id, updateRoomDto, payload.user.userId);
  }

  @Patch('join/:id')
  @ApiOkResponse({ type: Room })
  joinRoom(
    @Param('id') id: string,
    @Body() joinRoomDto: JoinRoomDto,
    @Req() payload: any,
  ) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.join(+id, joinRoomDto, payload.user.userId);
  }

  @Patch('leave/:id')
  @ApiOkResponse({ type: Room })
  leaveRoom(@Param('id') id: string, @Req() payload: any) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.leave(+id, payload.user.userId);
  }

  @Patch('ban/:id')
  @ApiOkResponse({ type: Room })
  banUser(
    @Param('id') id: string,
    @Req() payload: any,
    @Body() administrateRoomDto: AdministrateRoomDto,
  ) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.ban(+id, administrateRoomDto, payload.user.userId);
  }

  @Patch('unban/:id')
  @ApiOkResponse({ type: Room })
  unbanUser(
    @Param('id') id: string,
    @Req() payload: any,
    @Body() administrateRoomDto: AdministrateRoomDto,
  ) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.unban(
      +id,
      administrateRoomDto,
      payload.user.userId,
    );
  }

  @Patch('promote/:id')
  @ApiOkResponse({ type: Room })
  promoteUser(
    @Param('id') id: string,
    @Req() payload: any,
    @Body() administrateRoomDto: AdministrateRoomDto,
  ) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.promote(
      +id,
      administrateRoomDto,
      payload.user.userId,
    );
  }

  @Patch('demote/:id')
  @ApiOkResponse({ type: Room })
  demoteUser(
    @Param('id') id: string,
    @Req() payload: any,
    @Body() administrateRoomDto: AdministrateRoomDto,
  ) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.demote(
      +id,
      administrateRoomDto,
      payload.user.userId,
    );
  }

  @Patch('mute/:id')
  @ApiOkResponse({ type: Room })
  muteUser(
    @Param('id') id: string,
    @Req() payload: any,
    @Body() administrateRoomDto: AdministrateRoomDto,
  ) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.mute(
      +id,
      administrateRoomDto,
      payload.user.userId,
    );
  }

  @Patch('unmute/:id')
  @ApiOkResponse({ type: Room })
  unmuteUser(
    @Param('id') id: string,
    @Req() payload: any,
    @Body() administrateRoomDto: AdministrateRoomDto,
  ) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.unmute(
      +id,
      administrateRoomDto,
      payload.user.userId,
    );
  }

  @Patch('transferOwnership/:id')
  @ApiOkResponse({ type: Room })
  transferOwnershipToUser(
    @Param('id') id: string,
    @Req() payload: any,
    @Body() administrateRoomDto: AdministrateRoomDto,
  ) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.transferOwnership(
      +id,
      administrateRoomDto,
      payload.user.userId,
    );
  }

  @Delete(':id')
  @ApiOkResponse({ type: Room })
  remove(@Param('id') id: string, @Req() payload: any) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.roomsService.remove(+id, payload.user.userId);
  }
}
