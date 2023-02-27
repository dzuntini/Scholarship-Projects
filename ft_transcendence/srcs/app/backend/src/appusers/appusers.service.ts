import { HttpException, HttpStatus, Injectable } from '@nestjs/common';
import { CreateAppuserDto } from './dto/create-appuser.dto';
import { UpdateAppuserDto } from './dto/update-appuser.dto';
import { PrismaService } from 'src/prisma/prisma.service';
import { v4 as uuidv4 } from 'uuid';

@Injectable()
export class AppusersService {
  constructor(private prisma: PrismaService) {}

  exclude<User, Key extends keyof User>(
    user: User,
    keys: Key[],
  ): Omit<User, Key> {
    for (const key of keys) {
      delete user[key];
    }
    return user;
  }

  async create(CreateAppuserDto: CreateAppuserDto) {
    const exists = await this.prisma.aPPUser.findFirst({
      where: {
        pseudo: CreateAppuserDto.pseudo,
      },
    });
    if (exists != null) {
      CreateAppuserDto.pseudo = 'user' + uuidv4().substring(0, 8);
    }
    return this.exclude(
      await this.prisma.aPPUser.create({ data: CreateAppuserDto }),
      ['twoFactorAuthSecret'],
    );
  }

  async findAll() {
    const users = await this.prisma.aPPUser.findMany();
    const ret = [];
    for (let i = 0; i < users.length; i++) {
      ret.push(this.exclude(users[i], ['twoFactorAuthSecret']));
    }
    return ret;
  }

  async leaderboard() {
    const users = await this.prisma.aPPUser.findMany({
      orderBy: [
        {
          elo: 'desc',
        },
      ],
    });
    const ret = [];
    for (let i = 0; i < users.length && i < 500; i++) {
      ret.push(this.exclude(users[i], ['twoFactorAuthSecret']));
    }
    return ret;
  }

  async findOneByID(id: number) {
    const user = await this.prisma.aPPUser.findUnique({ where: { id } });
    if (user) {
      return this.exclude(user, ['twoFactorAuthSecret']);
    } else {
      throw new HttpException('User does not exist!', HttpStatus.NOT_FOUND);
    }
  }

  findOneByIDNoHide(id: number) {
    return this.prisma.aPPUser.findUnique({ where: { id: id } });
  }

  async findOneByLogin(login: string) {
    const user = await this.prisma.aPPUser.findUnique({ where: { login } });
    if (user) {
      return this.exclude(user, ['twoFactorAuthSecret']);
    } else {
      return null;
    }
  }

  async findAllFriends(id: number) {
    const user = await this.prisma.follows.findMany({
      where: {
        followingID: id,
      },
      include: {
        followed: true,
      },
    });
    return user.flatMap((it) => it.followed);
  }

  async findAllBlocked(id: number) {
    const user = await this.prisma.blocks.findMany({
      where: {
        blockerID: id,
      },
      include: {
        blocked: true,
      },
    });
    return user.flatMap((it) => it.blocked);
  }

  async findIsMyFriendById(userid: number, otherid: number) {
    if (userid === otherid) {
      throw new HttpException("Can't friend yourself", HttpStatus.BAD_REQUEST);
    }
    const check = await this.prisma.follows.findFirst({
      where: {
        followedID: otherid,
        followingID: userid,
      },
    });
    if (check === null) {
      return { friend: false };
    }
    return { friend: true };
  }

  async findIsBlockedById(userid: number, otherid: number) {
    if (userid === otherid) {
      throw new HttpException("Can't block yourself", HttpStatus.BAD_REQUEST);
    }
    const check = await this.prisma.blocks.findFirst({
      where: {
        blockedID: otherid,
        blockerID: userid,
      },
    });
    if (check === null) {
      return { blocked: false };
    }
    return { blocked: true };
  }

  async findAllGamesPlayerIn(id: number) {
    const data = await this.prisma.game.findMany({
      where: {
        OR: [
          {
            players: {
              some: {
                player2ID: id,
              },
            },
          },
          {
            players: {
              some: {
                player1ID: id,
              },
            },
          },
        ],
      },
      include: {
        players: {
          include: {
            Player1: true,
            Player2: true,
          },
        },
      },
      orderBy: {
        timestamp: 'desc',
      },
    });
    if (data === null) {
      return null;
    }
    const ret = [];
    data.forEach((element) => {
      ret.push({
        id: element.id,
        p1_score: element.p1_score,
        p2_score: element.p2_score,
        ranked: element.ranked,
        timestamp: element.timestamp,
        players: {
          Player1: this.exclude(element.players[0].Player1, [
            'twoFactorAuthSecret',
          ]),
          Player2: this.exclude(element.players[0].Player2, [
            'twoFactorAuthSecret',
          ]),
          player1ID: element.players[0].player1ID,
          player2ID: element.players[0].player2ID,
          gameID: element.players[0].gameID,
        },
      });
    });
    return ret;
  }

  async findDMWithUser(userid: number, otherid: number) {
    if (userid === otherid) {
      throw new HttpException("Can't DM with yourself", HttpStatus.FORBIDDEN);
    }
    const myDms = await this.prisma.room.findMany({
      where: {
        isdm: true,
        Access: {
          some: {
            appuserID: userid,
          },
        },
      },
      include: {
        Access: true,
      },
    });
    for (let i = 0; i < myDms.length; i++) {
      if (
        myDms[i].Access[0].appuserID === userid &&
        myDms[i].Access[1].appuserID === otherid
      ) {
        return this.exclude(myDms[i], ['password']);
      } else if (
        myDms[i].Access[0].appuserID === otherid &&
        myDms[i].Access[1].appuserID === userid
      ) {
        return this.exclude(myDms[i], ['password']);
      }
    }
    throw new HttpException('No DM found with this user', HttpStatus.NOT_FOUND);
  }

  async findIfUserIsMember(id: number, rid: number) {
    const leftroom = await this.prisma.access.findFirst({
      where: {
        appuserID: id,
        roomID: rid,
        AuthorizationID: 4,
      },
    });
    if (leftroom !== null) {
      throw new HttpException(
        'You have not joined this room ',
        HttpStatus.FORBIDDEN,
      );
    }
    const banned = await this.prisma.access.findFirst({
      where: {
        appuserID: id,
        roomID: rid,
        AuthorizationID: 6,
      },
    });
    if (banned !== null) {
      throw new HttpException(
        'You have been banned from this room ',
        HttpStatus.FORBIDDEN,
      );
    }
    const inroom = await this.prisma.access.findFirst({
      where: {
        appuserID: id,
        roomID: rid,
      },
    });
    if (!inroom) {
      throw new HttpException(
        'You have not joined this room ',
        HttpStatus.FORBIDDEN,
      );
    }
    const data = await this.prisma.room.findFirst({
      where: {
        id: rid,
      },
      include: {
        Access: true,
        messages: true,
      },
    });
    return this.exclude(data, ['password']);
  }

  async findAllRoomsMemberOf(id: number) {
    const data = await this.prisma.room.findMany({
      where: {
        Access: {
          none: {
            AuthorizationID: 4 || 6,
          },
          some: {
            appuserID: id,
          },
        },
      },
      include: {
        Access: true,
      },
    });
    const ret = [];
    data.forEach((element) => {
      ret.push(this.exclude(element, ['password']));
    });
    return ret;
  }

  async findAllRoomsOwnerOf(id: number) {
    const data = await this.prisma.aPPUser.findUnique({
      where: { id },
      include: { Access: true },
    });
    return data.Access.filter(function (obj) {
      return obj.AuthorizationID === 1;
    });
  }

  // Followed -> person being followed
  // Following -> person following

  // blocked -> person being blocked
  // blocker -> person that is blocking the other person

  async addFriend(userid: number, otherid: number) {
    if (userid == otherid) {
      throw new HttpException("Can't friend yourself!", HttpStatus.BAD_REQUEST);
    }
    const check = await this.prisma.follows.findFirst({
      where: {
        followedID: otherid,
        followingID: userid,
      },
    });
    if (check !== null) {
      throw new HttpException(
        'Already friends with this user',
        HttpStatus.BAD_REQUEST,
      );
    }
    const check2 = await this.prisma.blocks.findFirst({
      where: {
        blockedID: otherid,
        blockerID: userid,
      },
    });
    if (check2 !== null) {
      throw new HttpException(
        "Can't be friends with a user you have blocked",
        HttpStatus.FORBIDDEN,
      );
    }
    const check3 = await this.prisma.blocks.findFirst({
      where: {
        blockedID: userid,
        blockerID: otherid,
      },
    });
    if (check3 !== null) {
      throw new HttpException(
        "Can't be friends with a user that has blocked you",
        HttpStatus.FORBIDDEN,
      );
    }
    const user = await this.prisma.aPPUser.update({
      where: {
        id: userid,
      },
      data: {
        following: {
          upsert: {
            where: {
              followingID_followedID: {
                followedID: otherid,
                followingID: userid,
              },
            },
            create: {
              followed: {
                connect: { id: otherid },
              },
            },
            update: {
              followed: {
                connect: { id: otherid },
              },
            },
          },
        },
      },
      include: {
        followed: true,
        following: true,
      },
    });
    if (user) {
      return this.exclude(user, ['twoFactorAuthSecret']);
    } else {
      return null;
    }
  }

  async block(userid: number, otherid: number) {
    if (userid == otherid) {
      throw new HttpException("Can't block yourself!", HttpStatus.BAD_REQUEST);
    }
    const check = await this.prisma.follows.findFirst({
      where: {
        followedID: otherid,
        followingID: userid,
      },
    });
    if (check !== null) {
      throw new HttpException("Can't block a friend", HttpStatus.FORBIDDEN);
    }
    const check2 = await this.prisma.blocks.findFirst({
      where: {
        blockedID: otherid,
        blockerID: userid,
      },
    });
    if (check2 !== null) {
      throw new HttpException('User already blocked', HttpStatus.BAD_REQUEST);
    }
    const check3 = await this.prisma.follows.findFirst({
      where: {
        followedID: userid,
        followingID: otherid,
      },
    });
    if (check3 !== null) {
      await this.prisma.aPPUser.update({
        where: {
          id: otherid,
        },
        data: {
          following: {
            delete: {
              followingID_followedID: {
                followedID: userid,
                followingID: otherid,
              },
            },
          },
        },
      });
    }
    const user = await this.prisma.aPPUser.update({
      where: {
        id: userid,
      },
      data: {
        blocker: {
          upsert: {
            where: {
              blockerID_blockedID: {
                blockedID: otherid,
                blockerID: userid,
              },
            },
            create: {
              blocked: {
                connect: { id: otherid },
              },
            },
            update: {
              blocked: {
                connect: { id: otherid },
              },
            },
          },
        },
      },
    });
    if (user) {
      return this.exclude(user, ['twoFactorAuthSecret']);
    } else {
      return null;
    }
  }

  async removeFriend(userid: number, otherid: number) {
    if (userid == otherid) {
      throw new HttpException("Can't friend yourself!", HttpStatus.BAD_REQUEST);
    }
    const check = await this.prisma.follows.findFirst({
      where: {
        followedID: otherid,
        followingID: userid,
      },
    });
    if (check === null) {
      throw new HttpException(
        "Can't unfriend a user that isn't your friend",
        HttpStatus.BAD_REQUEST,
      );
    }
    const user = await this.prisma.aPPUser.update({
      where: {
        id: userid,
      },
      data: {
        following: {
          delete: {
            followingID_followedID: {
              followedID: otherid,
              followingID: userid,
            },
          },
        },
      },
    });
    if (user) {
      return this.exclude(user, ['twoFactorAuthSecret']);
    } else {
      return null;
    }
  }

  async unblock(userid: number, otherid: number) {
    if (userid == otherid) {
      throw new HttpException("Can't friend yourself!", HttpStatus.BAD_REQUEST);
    }
    const check = await this.prisma.blocks.findFirst({
      where: {
        blockedID: otherid,
        blockerID: userid,
      },
    });
    if (check === null) {
      throw new HttpException(
        "Can't unblock a user you haven't blocked",
        HttpStatus.BAD_REQUEST,
      );
    }
    const user = await this.prisma.aPPUser.update({
      where: {
        id: userid,
      },
      data: {
        blocker: {
          delete: {
            blockerID_blockedID: {
              blockedID: otherid,
              blockerID: userid,
            },
          },
        },
      },
    });
    if (user) {
      return this.exclude(user, ['twoFactorAuthSecret']);
    } else {
      return null;
    }
  }

  async setTwoFactorAuthenticationSecret(secret: string, id: number) {
    const user = await this.prisma.aPPUser.update({
      where: { id },
      data: {
        twoFactorAuthSecret: secret,
      },
    });

    if (user) {
      return this.exclude(user, ['twoFactorAuthSecret']);
    } else {
      return null;
    }
  }

  async toggleTwoFactorAuthentication(id: number) {
    const user = await this.prisma.aPPUser.findUnique({ where: { id } });
    if (user) {
      if (user.twoFactorAuthEnabled) {
        return this.exclude(
          await this.prisma.aPPUser.update({
            where: { id },
            data: {
              twoFactorAuthEnabled: false,
            },
          }),
          ['twoFactorAuthSecret'],
        );
      } else {
        return this.exclude(
          await this.prisma.aPPUser.update({
            where: { id },
            data: {
              twoFactorAuthEnabled: true,
            },
          }),
          ['twoFactorAuthSecret'],
        );
      }
    } else {
      return null;
    }
  }

  getImageMime(base64Encoded: string) {
    const mimeTypes = {
      png: 'image/png',
      gif: 'image/gif',
      jpg: 'image/jpeg',
      svg: 'image/svg+xml',
      webp: 'image/webp',
      jpeg: 'image/jpeg',
      pjpeg: 'image/jpeg',
      pjp: 'image/jpeg',
      jfif: 'image/jpeg',
    };
    // const prefix = atob(base64Encoded.slice(0, 60));
    const prefix = Buffer.from(base64Encoded.slice(0, 60), 'base64').toString();
    const found = prefix.match(
      /(webp)|(png)|(gif)|(svg)|(jpg)|(jpeg)|(pjpeg)|(pjp)|(jfif)/gi,
    );
    if (!found) {
      const hex = Buffer.from(base64Encoded, 'base64').toString('hex');
      if (hex.startsWith('ffd8ff')) return mimeTypes.jpeg;
      return null;
    } else {
      const type = found[0].toLocaleLowerCase();
      return mimeTypes[type];
    }
  }

  async update(id: number, UpdateAppuserDto: UpdateAppuserDto) {
    if (typeof UpdateAppuserDto.pseudo !== 'undefined') {
      if (
        (await this.prisma.aPPUser.findFirst({
          where: {
            pseudo: UpdateAppuserDto.pseudo,
          },
        })) !== null
      ) {
        throw new HttpException(
          "Can't have the same name as another user",
          HttpStatus.FORBIDDEN,
        );
      }
    }
    if (typeof UpdateAppuserDto.avatar !== 'undefined') {
      if (this.getImageMime(UpdateAppuserDto.avatar) === null) {
        throw new HttpException(
          'Image is not a valid image',
          HttpStatus.BAD_REQUEST,
        );
      }
    }
    const user = await this.prisma.aPPUser.update({
      where: { id },
      data: UpdateAppuserDto,
    });
    if (user) {
      return this.exclude(user, ['twoFactorAuthSecret']);
    } else {
      return null;
    }
  }

  async affect_elo(winnerID: number, looserID: number, gameType: boolean) {
    const winner = await this.prisma.aPPUser.findFirst({
      where: { id: winnerID },
    });
    const looser = await this.prisma.aPPUser.findFirst({
      where: { id: looserID },
    });
    const winnerChanceToWin =
      1 / (1 + Math.pow(10, (looser.elo - winner.elo) / 400));
    const delta = Math.round(32 * (1 - winnerChanceToWin));
    return [
      await this.prisma.aPPUser.update({
        where: {
          id: winner.id,
        },
        data: {
          elo: gameType ? winner.elo + delta : winner.elo,
          nb_played_game: winner.nb_played_game + 1,
          nb_victory: winner.nb_victory + 1,
        },
      }),
      await this.prisma.aPPUser.update({
        where: {
          id: looser.id,
        },
        data: {
          elo: gameType ? looser.elo - delta : looser.elo,
          nb_played_game: looser.nb_played_game + 1,
          nb_defeat: looser.nb_played_game + 1,
        },
      }),
    ];
  }
}
