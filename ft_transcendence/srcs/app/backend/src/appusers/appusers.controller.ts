import { JwtAuthGuard } from 'src/auth/jwt/jwt.guard';
import {
  Controller,
  Get,
  Body,
  Patch,
  Param,
  UseGuards,
  Req,
  BadRequestException,
} from '@nestjs/common';
import { ApiOkResponse, ApiTags } from '@nestjs/swagger';
import { Room } from 'src/rooms/entities/room.entity';
import { AppusersService } from './appusers.service';
import { UpdateAppuserDto } from './dto/update-appuser.dto';
import { Appuser } from './entities/appuser.entity';
import { Game } from 'src/games/entities/game.entity';

@Controller('appusers')
@ApiTags('Appusers')
@UseGuards(JwtAuthGuard)
export class AppusersController {
  constructor(private readonly appusersService: AppusersService) {}

  @Get()
  @ApiOkResponse({ type: Appuser, isArray: true })
  findAll() {
    return this.appusersService.findAll();
  }

  @Get('leaderboard')
  @ApiOkResponse({ type: Appuser, isArray: true })
  leaderboard() {
    return this.appusersService.leaderboard();
  }

  @Get('me')
  @ApiOkResponse({ type: Appuser })
  findMe(@Req() payload) {
    return this.appusersService.findOneByID(payload.user.userId);
  }

  @Patch('me/addfriend/:id')
  @ApiOkResponse({ type: Appuser })
  addFriend(@Req() payload, @Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    } else if (payload.user.userId === +id) {
      throw new BadRequestException();
    }
    return this.appusersService.addFriend(payload.user.userId, +id);
  }

  @Patch('me/block/:id')
  @ApiOkResponse({ type: Appuser })
  addBlock(@Req() payload, @Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    } else if (payload.user.userId === +id) {
      throw new BadRequestException();
    }
    return this.appusersService.block(payload.user.userId, +id);
  }

  @Patch('me/removefriend/:id')
  @ApiOkResponse({ type: Appuser })
  removeFriend(@Req() payload, @Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    } else if (payload.user.userId === +id) {
      throw new BadRequestException();
    }
    return this.appusersService.removeFriend(payload.user.userId, +id);
  }

  @Patch('me/unblock/:id')
  @ApiOkResponse({ type: Appuser })
  removeBlock(@Req() payload, @Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    } else if (payload.user.userId === +id) {
      throw new BadRequestException();
    }
    return this.appusersService.unblock(payload.user.userId, +id);
  }

  @Get('me/friends')
  @ApiOkResponse({ type: Appuser, isArray: true })
  findFriends(@Req() payload) {
    return this.appusersService.findAllFriends(payload.user.userId);
  }

  @Get('me/blocked')
  @ApiOkResponse({ type: Appuser, isArray: true })
  findBlocked(@Req() payload) {
    return this.appusersService.findAllBlocked(payload.user.userId);
  }

  @Get('me/hasdm/:id')
  @ApiOkResponse({ type: Room })
  findDM(@Req() payload, @Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.appusersService.findDMWithUser(payload.user.userId, +id);
  }

  @Get('me/member/:id')
  @ApiOkResponse({ type: Room })
  findRoomMemberOf(@Req() payload, @Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.appusersService.findIfUserIsMember(payload.user.userId, +id);
  }

  @Get('me/member')
  @ApiOkResponse({ type: Room, isArray: true })
  findRoomMember(@Req() payload) {
    return this.appusersService.findAllRoomsMemberOf(payload.user.userId);
  }

  @Get('me/owner')
  @ApiOkResponse({ type: Room, isArray: true })
  findRoomOwner(@Req() payload) {
    return this.appusersService.findAllRoomsOwnerOf(payload.user.userId);
  }

  @Get('me/player')
  @ApiOkResponse({ type: Game, isArray: true })
  findGamePlayedIn(@Req() payload) {
    return this.appusersService.findAllGamesPlayerIn(payload.user.userId);
  }

  @Get(':id')
  @ApiOkResponse({ type: Appuser })
  findOneByID(@Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.appusersService.findOneByID(+id);
  }

  @Get(':id/friends')
  @ApiOkResponse({ type: Appuser })
  findFriendsByID(@Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.appusersService.findAllFriends(+id);
  }

  @Get(':id/myfriend')
  @ApiOkResponse({ type: Appuser })
  findIsMyFriendByID(@Req() payload, @Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.appusersService.findIsMyFriendById(payload.user.userId, +id);
  }

  @Get(':id/blockedbyme')
  @ApiOkResponse({ type: Appuser })
  findIsBlockedByID(@Req() payload, @Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.appusersService.findIsBlockedById(payload.user.userId, +id);
  }

  @Get(':id/player')
  @ApiOkResponse({ type: Appuser })
  findGamesPlayedInByID(@Req() payload, @Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.appusersService.findAllGamesPlayerIn(+id);
  }

  @Patch('me')
  @ApiOkResponse({ type: Appuser })
  update(@Req() req, @Body() updateAppuserDto: UpdateAppuserDto) {
    return this.appusersService.update(req.user.userId, updateAppuserDto);
  }
}
