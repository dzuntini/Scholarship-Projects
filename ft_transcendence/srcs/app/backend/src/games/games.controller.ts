import { JwtAuthGuard } from 'src/auth/jwt/jwt.guard';
import {
  Controller,
  Get,
  Param,
  UseGuards,
  BadRequestException,
} from '@nestjs/common';
import { ApiOkResponse, ApiTags } from '@nestjs/swagger';
import { GamesService } from './games.service';
import { Game } from './entities/game.entity';

@Controller('games')
@ApiTags('Games')
@UseGuards(JwtAuthGuard)
export class GamesController {
  constructor(private readonly gamesService: GamesService) {}

  @Get()
  @ApiOkResponse({ type: Game, isArray: true })
  findAll() {
    return this.gamesService.findAll();
  }

  @Get(':id')
  @ApiOkResponse({ type: Game })
  findOne(@Param('id') id: string) {
    if (isNaN(+id)) {
      throw new BadRequestException();
    }
    return this.gamesService.findOne(+id);
  }
}
