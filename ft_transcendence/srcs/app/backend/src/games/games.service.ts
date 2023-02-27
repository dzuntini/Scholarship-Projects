import { Injectable } from '@nestjs/common';
import { CreateGameDto } from './dto/create-game.dto';
import { PrismaService } from 'src/prisma/prisma.service';
import { AppusersService } from 'src/appusers/appusers.service';
import { GameStatus } from 'src/sockets/game/game.dto';

@Injectable()
export class GamesService {
  constructor(
    private usersService: AppusersService,
    private prisma: PrismaService,
  ) {}

  async create(
    gameDTO: CreateGameDto,
    Player1ID: number,
    Player2ID: number,
    gameStatus: GameStatus,
  ) {
    const data = {
      ...gameDTO,
      status: {
        create: {
          Status: {
            connect: { id: gameStatus === GameStatus.Finished ? 1 : 2 },
          },
        },
      },
      players: {
        create: {
          Player1: {
            connect: { id: Player1ID },
          },
          Player2: {
            connect: { id: Player2ID },
          },
        },
      },
    };
    if (gameStatus > GameStatus.WaitingPlayers) {
      // console.log("player 1: " + gameDTO.p1_score + "vs player 2: " + gameDTO.p2_score);
      gameDTO.p1_score > gameDTO.p2_score
        ? await this.usersService.affect_elo(
            Player1ID,
            Player2ID,
            gameDTO.ranked,
          )
        : await this.usersService.affect_elo(
            Player2ID,
            Player1ID,
            gameDTO.ranked,
          );
    }
    // console.log(data);
    return this.prisma.game.create({ data: data });
  }

  findAll() {
    return this.prisma.game.findMany();
  }

  findOne(id: number) {
    return this.prisma.game.findUnique({ where: { id } });
  }

  remove(id: number) {
    return this.prisma.game.delete({ where: { id } });
  }
}
