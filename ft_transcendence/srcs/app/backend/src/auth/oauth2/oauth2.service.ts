import { HttpService } from '@nestjs/axios';
import { Injectable } from '@nestjs/common';
import { AppusersService } from 'src/appusers/appusers.service';
import * as fs from 'fs';
import * as fsp from 'fs/promises';
import * as https from 'https';
import {v4 as uuidv4} from 'uuid';
import * as sharp from 'sharp';

@Injectable()
export class oAuth2Service {
  constructor(
    private readonly APPUserService: AppusersService,
    private httpService: HttpService,
  ) {}

  async fetchUserProfileImage(avatarURL: string) {
    return new Promise<Buffer>((resolve, reject) => {
      const file_name = './temp/' + uuidv4() + '.data';
      const file = fs.createWriteStream(file_name);
      const req = https.get(avatarURL, async (response) => {
        response.pipe(file);

        response.on('error', (err) => {
          reject(err);
        });

        file.on('finish', async () => {
          file.close();
          const data = await sharp(await fsp.readFile(file_name))
            .resize(256, 256)
            .png()
            .toBuffer();
          fsp.unlink(file_name);
          resolve(data);
        });
        req.end();
      });
    });
  }

  async findUserFrom(login: string, avatarURL: string): Promise<any> {
    const user = await this.APPUserService.findOneByLogin(login);
    if (!user) {
      const data = await this.fetchUserProfileImage(avatarURL);
      return this.APPUserService.create({
        login: login,
        pseudo: login,
        avatar: data.toString('base64'),
      });
    }
    return user;
  }
}
