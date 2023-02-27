import {
  BadRequestException,
  HttpException,
  HttpStatus,
  Injectable,
  NotFoundException,
  UnauthorizedException,
} from '@nestjs/common';
import { CreateRoomDto } from './dto/create-room.dto';
import { UpdateRoomDto } from './dto/update-room.dto';
import { PrismaService } from 'src/prisma/prisma.service';
import { ConfigService } from '@nestjs/config';
import { JoinRoomDto } from './dto/join-room.dto';
import { AdministrateRoomDto } from './dto/administrate-room.dto';
import { AppusersService } from 'src/appusers/appusers.service';
import { Room } from '@prisma/client';
import { v4 as uuidv4 } from 'uuid';
// bcrypt does not work import {} from file
// eslint-disable-next-line @typescript-eslint/no-var-requires
const bcrypt = require('bcrypt');

export type AuthID = {
  Owner: 1;
  Admin: 2;
  User: 3;
  Left: 4;
  Mute: 5;
  Banned: 6;
};

@Injectable()
export class RoomsService {
  constructor(
    private prisma: PrismaService,
    private configService: ConfigService,
    private appusersService: AppusersService,
  ) {}

  async create(createRoomDto: CreateRoomDto, user: any) {
    if (
      (await this.prisma.room.findFirst({
        where: {
          name: createRoomDto.name,
        },
      })) !== null
    ) {
      throw new HttpException(
        "Can't create a room with name " +
          createRoomDto.name +
          ', another room already exists with that name!',
        HttpStatus.FORBIDDEN,
      );
    }
    const data = {
      ...createRoomDto,
      haspass: false,
      Access: {
        create: {
          appuser: {
            connect: { id: user.userId },
          },
          Authorization: {
            connect: { id: 1 },
          },
        },
      },
    };
    if (data.password !== '' && data.password !== undefined) {
      data.password = await bcrypt.hash(
        data.password,
        this.configService.get<number>('salt'),
      );
      data.haspass = true;
    }
    return this.appusersService.exclude(
      await this.prisma.room.create({
        data: data,
        include: {
          Access: true,
        },
      }),
      ['password'],
    );
  }

  async createDM(userId: number, otherId: number, forGame?: true) {
    if (userId === otherId) {
      throw new HttpException("Can't DM Yourself", HttpStatus.FORBIDDEN);
    }
    if (
      (await this.prisma.blocks.findFirst({
        where: {
          OR: [
            {
              blockedID: userId,
              blockerID: otherId,
            },
            {
              blockedID: otherId,
              blockerID: userId,
            },
          ],
        },
        // eslint-disable-next-line prettier/prettier
      })) != null) {
      if (forGame && forGame === true)
        throw new HttpException(
          'Cannot challenge a user that has blocked you or a user you have blocked',
          HttpStatus.FORBIDDEN,
        );
      throw new HttpException(
        'Cannot DM with a user that has blocked you or a user you have blocked',
        HttpStatus.FORBIDDEN,
      );
    }
    const myDms = await this.prisma.room.findMany({
      where: {
        isdm: true,
        Access: {
          some: {
            appuserID: userId,
          },
        },
      },
      include: {
        Access: true,
      },
    });
    for (let i = 0; i < myDms.length; i++) {
      if (
        myDms[i].Access[0].appuserID == userId &&
        myDms[i].Access[1].appuserID == otherId
      ) {
        if (forGame && forGame === true)
          return this.appusersService.exclude(myDms[i], ['password']);
        throw new HttpException(
          'Cannot create a DM with a user that you already have a DM with.',
          HttpStatus.FORBIDDEN,
        );
      } else if (
        myDms[i].Access[0].appuserID == userId &&
        myDms[i].Access[1].appuserID == otherId
      ) {
        if (forGame && forGame === true)
          return this.appusersService.exclude(myDms[i], ['password']);
        throw new HttpException(
          'Cannot create a DM with a user that you already have a DM with.',
          HttpStatus.FORBIDDEN,
        );
      }
    }
    const data = await this.prisma.room.create({
      data: {
        haspass: false,
        name: 'DM-' + userId + '-' + otherId + '-' + uuidv4(),
        password: '',
        isdm: true,
        visible: false,
        Access: {
          create: {
            Authorization: {
              connect: { id: 3 },
            },
            appuser: {
              connect: { id: userId },
            },
          },
        },
      },
    });
    return this.appusersService.exclude(
      await this.prisma.room.update({
        where: { id: data.id },
        data: {
          Access: {
            upsert: {
              where: {
                appuserID_AuthorizationID_roomID: {
                  appuserID: otherId,
                  roomID: data.id,
                  AuthorizationID: 4,
                },
              },
              create: {
                appuser: {
                  connect: { id: otherId },
                },
                Authorization: {
                  connect: { id: 3 },
                },
              },
              update: {
                Authorization: {
                  connect: { id: 3 },
                },
              },
            },
          },
        },
        include: {
          Access: true,
        },
      }),
      ['password'],
    );
  }

  async getAll() {
    return this.prisma.room.findMany();
  }

  async getAllNotDM() {
    return this.prisma.room.findMany({
      where: {
        isdm: false,
      },
    });
  }

  async getAllDM() {
    return this.prisma.room.findMany({
      where: {
        isdm: true,
      },
    });
  }

  // really?
  async getOneDM(userid: number, otherid: number) {
    if (userid === otherid) {
      return undefined;
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
        return this.appusersService.exclude(myDms[i], ['password']);
      } else if (
        myDms[i].Access[0].appuserID === otherid &&
        myDms[i].Access[1].appuserID === userid
      ) {
        return this.appusersService.exclude(myDms[i], ['password']);
      }
    }
    return null;
  }

  async findAll(userId: number) {
    const rooms = await this.prisma.room.findMany({
      where: {
        OR: [
          {
            visible: {
              equals: true,
            },
          },
          {
            Access: {
              some: {
                appuserID: userId,
              },
              none: {
                OR: [
                  {
                    appuserID: userId,
                    AuthorizationID: 4,
                  },
                  {
                    appuserID: userId,
                    AuthorizationID: 6,
                  },
                ],
              },
            },
          },
        ],
      },
      include: {
        Access: true,
      },
    });
    const ret = [];
    for (let i = 0; i < rooms.length; i++) {
      ret.push(this.appusersService.exclude(rooms[i], ['password']));
    }
    return ret;
  }

  async findOneBackend(id: number) {
    return await this.prisma.room.findFirst({
      where: {
        id,
      },
      include: {
        Access: true,
      },
    });
  }

  async findOne(id: number, userId: number) {
    const room = await this.prisma.room.findFirst({
      where: {
        id: id,
        OR: [
          {
            visible: {
              equals: true,
            },
          },
          {
            Access: {
              some: {
                appuserID: userId,
              },
              none: {
                OR: [
                  {
                    appuserID: userId,
                    AuthorizationID: 4,
                  },
                  {
                    appuserID: userId,
                    AuthorizationID: 6,
                  },
                ],
              },
            },
          },
        ],
      },
      include: {
        Access: true,
        messages: true,
      },
    });
    if (room) {
      return this.appusersService.exclude(room, ['password']);
    } else {
      return null;
    }
  }

  async findOneByName(name: string) {
    const data = await this.prisma.room.findFirst({
      where: {
        name,
      },
    });
    if (data !== null) {
      return {
        id: data.id,
      };
    } else {
      throw new HttpException(
        'No room has name ' + name + '!',
        HttpStatus.NOT_FOUND,
      );
    }
  }

  async getMembersOfRoom(id: number, userId: number) {
    const notinroom = await this.prisma.access.findFirst({
      where: {
        OR: [
          {
            appuserID: userId,
            roomID: id,
            AuthorizationID: 4,
          },
          {
            appuserID: userId,
            roomID: id,
            AuthorizationID: 6,
          },
        ],
      },
    });
    if (notinroom !== null) {
      throw new HttpException(
        'You have not joined room with ' + id,
        HttpStatus.FORBIDDEN,
      );
    }
    const data = await this.prisma.room.findFirst({
      where: {
        id: id,
      },
      include: {
        Access: true,
      },
    });
    if (data === null) return data;
    const ret = [];
    for (const d of data.Access) {
      ret.push(await this.appusersService.findOneByID(d.appuserID));
    }
    return ret;
  }

  async getMessagesOfRoom(id: number, userId: number) {
    const data = await this.prisma.room.findFirst({
      where: {
        id: id,
        Access: {
          some: {
            appuserID: userId,
          },
          none: {
            OR: [
              {
                appuserID: userId,
                AuthorizationID: 4,
              },
              {
                appuserID: userId,
                AuthorizationID: 6,
              },
            ],
          },
        },
      },
      include: {
        messages: {
          include: {
            appuser: true,
          },
        },
      },
    });
    if (data === null) return data;
    const ret = [];
    for (const b of data.messages) {
      ret.push(b);
      ret.at(-1).appuser = this.appusersService.exclude(ret.at(-1).appuser, [
        'twoFactorAuthSecret',
      ]);
    }
    return data.messages.sort((a, b) => (a.timestamp > b.timestamp ? 1 : -1));
  }

  async update(roomid: number, updateRoomDto: UpdateRoomDto, userId: number) {
    // console.log(updateRoomDto);
    const user = await this.prisma.access.findFirst({
      where: {
        OR: [
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 1,
          },
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 2,
          },
        ],
      },
    });
    if (user) {
      if (updateRoomDto.name !== undefined) {
        const check1 = await this.prisma.room.findFirst({
          where: {
            name: updateRoomDto.name,
          },
        });
        if (check1 !== null && check1.id !== roomid) {
          throw new HttpException(
            "Can't update room name to " +
              updateRoomDto.name +
              ', another room already exists with that name!',
            HttpStatus.FORBIDDEN,
          );
        }
      }
      if (typeof updateRoomDto.password === 'string') {
        const new_data = {
          ...updateRoomDto,
          haspass: false,
        };
        if (updateRoomDto.password === '') {
          new_data.password = '';
          new_data.haspass = false;
        } else {
          new_data.password = await bcrypt.hash(
            updateRoomDto.password,
            this.configService.get<number>('salt'),
          );
          new_data.haspass = true;
        }
        const room = await this.prisma.room.update({
          where: { id: roomid },
          data: new_data,
        });
        if (room) {
          return this.appusersService.exclude(room, ['password']);
        } else {
          return null;
        }
      }
      const room = await this.prisma.room.update({
        where: { id: roomid },
        data: updateRoomDto,
      });
      // console.log(room);
      if (room) {
        return this.appusersService.exclude(room, ['password']);
      } else {
        return null;
      }
    }
    throw new UnauthorizedException();
  }

  async join(roomid: number, joinRoomDto: JoinRoomDto, userId: number) {
    if (roomid === undefined) {
      throw new BadRequestException();
    }
    const check1 = await this.prisma.access.findFirst({
      where: {
        OR: [
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 1,
          },
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 2,
          },
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 3,
          },
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 5,
          },
        ],
      },
    });
    if (check1 !== null) {
      throw new HttpException(
        'Unable to join this room, already in the room',
        HttpStatus.FORBIDDEN,
      );
    }
    const check2 = await this.prisma.access.findFirst({
      where: {
        appuserID: userId,
        roomID: roomid,
        AuthorizationID: 6,
      },
    });
    if (check2 !== null) {
      throw new HttpException(
        "You're banned from this room",
        HttpStatus.FORBIDDEN,
      );
    }
    const data = await this.prisma.room.findUnique({
      where: {
        id: roomid,
      },
    });
    if (data === null) {
      throw new HttpException(
        "Can't join a room that doesn't exist!",
        HttpStatus.BAD_REQUEST,
      );
    } else if (data.isdm) {
      throw new HttpException("Can't join a DM", HttpStatus.FORBIDDEN);
    } else if (data.haspass) {
      if (
        typeof joinRoomDto.password === 'undefined' ||
        joinRoomDto.password === '' ||
        joinRoomDto.password === null
      ) {
        throw new BadRequestException();
      }
      const confirm: boolean = await bcrypt.compare(
        joinRoomDto.password,
        data.password,
      );
      if (!confirm) {
        throw new HttpException(
          'Incorrect password for room ' + data.name,
          HttpStatus.UNAUTHORIZED,
        );
      }
    }
    try {
      const room = await this.prisma.room.update({
        where: {
          id: roomid,
        },
        data: {
          Access: {
            upsert: {
              where: {
                appuserID_AuthorizationID_roomID: {
                  appuserID: userId,
                  roomID: roomid,
                  AuthorizationID: 4,
                },
              },
              create: {
                appuser: {
                  connect: { id: userId },
                },
                Authorization: {
                  connect: { id: 3 },
                },
              },
              update: {
                Authorization: {
                  connect: { id: 3 },
                },
              },
            },
          },
        },
        include: {
          Access: true,
        },
      });
      if (room) {
        return this.appusersService.exclude(room, ['password']);
      } else {
        return null;
      }
    } catch {
      throw new HttpException(
        'To many join attempts, try again later',
        HttpStatus.TOO_MANY_REQUESTS,
      );
    }
  }

  async leave(roomid: number, userId: number) {
    const user = await this.prisma.access.findFirst({
      where: {
        appuserID: userId,
        roomID: roomid,
      },
    });
    const r = await this.prisma.room.findFirst({
      where: {
        id: roomid,
      },
    });
    if (r.isdm) {
      throw new HttpException("Can't leave a DM!", HttpStatus.FORBIDDEN);
    }
    if (user) {
      if (user.AuthorizationID === 1) {
        throw new HttpException(
          "Can't leave the room while You're the owner!",
          HttpStatus.FORBIDDEN,
        );
      }
      if (user.AuthorizationID === 4 || user.AuthorizationID === 6) {
        throw new HttpException(
          "You're not part of this room!",
          HttpStatus.FORBIDDEN,
        );
      }
      return this.prisma.room.update({
        where: { id: roomid },
        data: {
          Access: {
            update: {
              where: {
                appuserID_AuthorizationID_roomID: {
                  AuthorizationID: user.AuthorizationID,
                  appuserID: userId,
                  roomID: roomid,
                },
              },
              data: {
                Authorization: {
                  connect: { id: 4 },
                },
              },
            },
          },
        },
      });
    }
    return new NotFoundException();
  }

  async ban(
    roomid: number,
    administrateRoomDto: AdministrateRoomDto,
    userId: number,
  ) {
    if (userId === administrateRoomDto.appuserID) {
      throw new HttpException("Can't ban yourself", HttpStatus.BAD_REQUEST);
    }
    const user = await this.prisma.access.findFirst({
      where: {
        OR: [
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 1,
          },
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 2,
          },
        ],
      },
    });
    if (user) {
      const victim = await this.prisma.access.findFirst({
        where: {
          appuserID: administrateRoomDto.appuserID,
          roomID: roomid,
        },
      });
      if (victim) {
        if (victim.AuthorizationID == 1 || victim.AuthorizationID == 2) {
          throw new HttpException(
            "Can't ban an Admin or the Owner",
            HttpStatus.FORBIDDEN,
          );
        } else if (victim.AuthorizationID == 6) {
          throw new HttpException(
            'User already banned!',
            HttpStatus.BAD_REQUEST,
          );
        } else {
          const room = await this.prisma.room.update({
            where: { id: roomid },
            data: {
              Access: {
                update: {
                  where: {
                    appuserID_AuthorizationID_roomID: {
                      AuthorizationID: victim.AuthorizationID,
                      appuserID: victim.appuserID,
                      roomID: roomid,
                    },
                  },
                  data: {
                    Authorization: {
                      connect: { id: 6 },
                    },
                  },
                },
              },
            },
            include: {
              Access: true,
            },
          });
          if (room) {
            return this.appusersService.exclude(room, ['password']);
          } else {
            return null;
          }
        }
      } else {
        throw new HttpException(
          "User not in room, can't ban this user",
          HttpStatus.BAD_REQUEST,
        );
      }
    }
    throw new HttpException(
      "You don't have the permissions to perform this action",
      HttpStatus.UNAUTHORIZED,
    );
  }

  async unban(
    roomid: number,
    administrateRoomDto: AdministrateRoomDto,
    userId: number,
  ) {
    if (userId === administrateRoomDto.appuserID) {
      throw new HttpException("Can't unban yourself", HttpStatus.BAD_REQUEST);
    }
    const user = await this.prisma.access.findFirst({
      where: {
        OR: [
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 1,
          },
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 2,
          },
        ],
      },
    });
    if (user) {
      const victim = await this.prisma.access.findFirst({
        where: {
          appuserID: administrateRoomDto.appuserID,
          roomID: roomid,
          AuthorizationID: 6,
        },
      });
      if (victim) {
        const room = await this.prisma.room.update({
          where: { id: roomid },
          data: {
            Access: {
              update: {
                where: {
                  appuserID_AuthorizationID_roomID: {
                    AuthorizationID: victim.AuthorizationID,
                    appuserID: victim.appuserID,
                    roomID: roomid,
                  },
                },
                data: {
                  Authorization: {
                    connect: { id: 4 },
                  },
                },
              },
            },
          },
          include: {
            Access: true,
          },
        });
        if (room) {
          return this.appusersService.exclude(room, ['password']);
        } else {
          return null;
        }
      } else {
        throw new HttpException('User is not banned', HttpStatus.BAD_REQUEST);
      }
    }
    throw new HttpException(
      "You don't have the permissions to perform this action",
      HttpStatus.UNAUTHORIZED,
    );
  }

  async promote(
    roomid: number,
    administrateRoomDto: AdministrateRoomDto,
    userId: number,
  ) {
    if (userId === administrateRoomDto.appuserID) {
      throw new HttpException("Can't promote yourself", HttpStatus.BAD_REQUEST);
    }
    const user = await this.prisma.access.findFirst({
      where: {
        appuserID: userId,
        roomID: roomid,
        AuthorizationID: 1,
      },
    });
    // console.log(user);
    if (user) {
      const victim = await this.prisma.access.findFirst({
        where: {
          appuserID: administrateRoomDto.appuserID,
          roomID: roomid,
          AuthorizationID: 3,
        },
      });
      // console.log(victim);
      if (victim) {
        if (victim.AuthorizationID === 3) {
          const room = await this.prisma.room.update({
            where: { id: roomid },
            data: {
              Access: {
                update: {
                  where: {
                    appuserID_AuthorizationID_roomID: {
                      AuthorizationID: victim.AuthorizationID,
                      appuserID: victim.appuserID,
                      roomID: roomid,
                    },
                  },
                  data: {
                    Authorization: {
                      connect: { id: 2 },
                    },
                  },
                },
              },
            },
            include: {
              Access: true,
            },
          });
          if (room) {
            return this.appusersService.exclude(room, ['password']);
          } else {
            return null;
          }
        }
      }
    }
    throw new HttpException(
      "You don't have the permissions to perform this action",
      HttpStatus.UNAUTHORIZED,
    );
  }

  async demote(
    roomid: number,
    administrateRoomDto: AdministrateRoomDto,
    userId: number,
  ) {
    if (userId === administrateRoomDto.appuserID) {
      throw new HttpException("Can't demote yourself", HttpStatus.BAD_REQUEST);
    }
    const user = await this.prisma.access.findFirst({
      where: {
        appuserID: userId,
        roomID: roomid,
        AuthorizationID: 1,
      },
    });
    if (user) {
      const victim = await this.prisma.access.findFirst({
        where: {
          appuserID: administrateRoomDto.appuserID,
          roomID: roomid,
          AuthorizationID: 2,
        },
      });
      if (victim) {
        const room = await this.prisma.room.update({
          where: { id: roomid },
          data: {
            Access: {
              update: {
                where: {
                  appuserID_AuthorizationID_roomID: {
                    AuthorizationID: victim.AuthorizationID,
                    appuserID: victim.appuserID,
                    roomID: roomid,
                  },
                },
                data: {
                  Authorization: {
                    connect: { id: 3 },
                  },
                },
              },
            },
          },
          include: {
            Access: true,
          },
        });
        if (room) {
          return this.appusersService.exclude(room, ['password']);
        } else {
          return null;
        }
      } else {
        throw new HttpException(
          "User isn't a administrator!",
          HttpStatus.BAD_REQUEST,
        );
      }
    }
    throw new HttpException(
      "You don't have the permissions to perform this action",
      HttpStatus.UNAUTHORIZED,
    );
  }

  async mute(
    roomid: number,
    administrateRoomDto: AdministrateRoomDto,
    userId: number,
  ) {
    if (userId === administrateRoomDto.appuserID) {
      throw new HttpException("Can't mute yourself", HttpStatus.BAD_REQUEST);
    }
    const user = await this.prisma.access.findFirst({
      where: {
        OR: [
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 1,
          },
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 2,
          },
        ],
      },
    });
    if (user) {
      const victim = await this.prisma.access.findFirst({
        where: {
          appuserID: administrateRoomDto.appuserID,
          roomID: roomid,
          AuthorizationID: 3,
        },
      });
      if (victim) {
        const room = await this.prisma.room.update({
          where: { id: roomid },
          data: {
            Access: {
              update: {
                where: {
                  appuserID_AuthorizationID_roomID: {
                    AuthorizationID: victim.AuthorizationID,
                    appuserID: victim.appuserID,
                    roomID: roomid,
                  },
                },
                data: {
                  Authorization: {
                    connect: { id: 5 },
                  },
                },
              },
            },
          },
          include: {
            Access: true,
          },
        });
        if (room) {
          return this.appusersService.exclude(room, ['password']);
        } else {
          return null;
        }
      } else {
        throw new HttpException(
          "Can't mute this user, not a normal member!",
          HttpStatus.BAD_REQUEST,
        );
      }
    }
    throw new HttpException(
      "You don't have the permissions to perform this action",
      HttpStatus.UNAUTHORIZED,
    );
  }

  async unmute(
    roomid: number,
    administrateRoomDto: AdministrateRoomDto,
    userId: number,
  ) {
    if (userId === administrateRoomDto.appuserID) {
      throw new HttpException("Can't unmute yourself", HttpStatus.BAD_REQUEST);
    }
    const user = await this.prisma.access.findFirst({
      where: {
        OR: [
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 1,
          },
          {
            appuserID: userId,
            roomID: roomid,
            AuthorizationID: 2,
          },
        ],
      },
    });
    if (user) {
      const victim = await this.prisma.access.findFirst({
        where: {
          appuserID: administrateRoomDto.appuserID,
          roomID: roomid,
          AuthorizationID: 5,
        },
      });
      if (victim) {
        const room = await this.prisma.room.update({
          where: { id: roomid },
          data: {
            Access: {
              update: {
                where: {
                  appuserID_AuthorizationID_roomID: {
                    AuthorizationID: victim.AuthorizationID,
                    appuserID: victim.appuserID,
                    roomID: roomid,
                  },
                },
                data: {
                  Authorization: {
                    connect: { id: 3 },
                  },
                },
              },
            },
          },
          include: {
            Access: true,
          },
        });
        if (room) {
          return this.appusersService.exclude(room, ['password']);
        } else {
          return null;
        }
      } else {
        throw new HttpException(
          'Unable to unmute user, not muted',
          HttpStatus.BAD_REQUEST,
        );
      }
    }
    throw new HttpException(
      "You don't have the permissions to perform this action",
      HttpStatus.UNAUTHORIZED,
    );
  }

  async transferOwnership(
    roomid: number,
    administrateRoomDto: AdministrateRoomDto,
    userId: number,
  ) {
    if (userId === administrateRoomDto.appuserID) {
      throw new HttpException(
        "Can't transfer ownership to yourself",
        HttpStatus.BAD_REQUEST,
      );
    }
    const user = await this.prisma.access.findFirst({
      where: {
        appuserID: userId,
        roomID: roomid,
        AuthorizationID: 1,
      },
    });
    if (user) {
      const victim = await this.prisma.access.findFirst({
        where: {
          appuserID: administrateRoomDto.appuserID,
          roomID: roomid,
          AuthorizationID: 2,
        },
      });
      if (victim) {
        const room = await this.prisma.room.update({
          where: { id: roomid },
          data: {
            Access: {
              update: [
                {
                  where: {
                    appuserID_AuthorizationID_roomID: {
                      AuthorizationID: victim.AuthorizationID,
                      appuserID: victim.appuserID,
                      roomID: roomid,
                    },
                  },
                  data: {
                    Authorization: {
                      connect: { id: 1 },
                    },
                  },
                },
                {
                  where: {
                    appuserID_AuthorizationID_roomID: {
                      AuthorizationID: user.AuthorizationID,
                      appuserID: user.appuserID,
                      roomID: roomid,
                    },
                  },
                  data: {
                    Authorization: {
                      connect: { id: 2 },
                    },
                  },
                },
              ],
            },
          },
          include: {
            Access: true,
          },
        });
        if (room) {
          return this.appusersService.exclude(room, ['password']);
        } else {
          return null;
        }
      } else {
        throw new HttpException(
          "User isn't an administrator of the room",
          HttpStatus.BAD_REQUEST,
        );
      }
    }
    throw new HttpException(
      "You don't have the permissions to perform this action",
      HttpStatus.UNAUTHORIZED,
    );
  }

  async remove(roomid: number, userId: number) {
    const user = await this.prisma.access.findFirst({
      where: {
        appuserID: userId,
        roomID: roomid,
        AuthorizationID: 1,
      },
    });
    if (user) {
      const room = await this.prisma.room.delete({ where: { id: roomid } });
      if (room) {
        return this.appusersService.exclude(room, ['password']);
      } else {
        return null;
      }
    }
    throw new HttpException(
      "You don't have the permissions to perform this action",
      HttpStatus.UNAUTHORIZED,
    );
  }

  async addMessageToRoom(
    channelID: number,
    userID: number,
    message: string,
  ): Promise<Omit<Room, 'password'>> {
    const room = await this.prisma.room.update({
      where: { id: channelID },
      data: {
        messages: {
          create: {
            appuser: {
              connect: {
                id: userID,
              },
            },
            content: message,
          },
        },
      },
    });
    if (room) {
      return this.appusersService.exclude(room, ['password']);
    } else {
      return null;
    }
  }
}
