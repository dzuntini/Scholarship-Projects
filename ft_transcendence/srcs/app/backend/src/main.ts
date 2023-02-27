import { ValidationPipe } from '@nestjs/common';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { PrismaService } from './prisma/prisma.service';
import { SwaggerModule, DocumentBuilder } from '@nestjs/swagger';
import { ConfigService } from '@nestjs/config';
import { NestExpressApplication } from '@nestjs/platform-express';
import * as compression from 'compression';
import { json } from 'express';

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);
  const configService: ConfigService = app.get(ConfigService);
  app.enableCors({
    origin: '*',
    methods: ['GET', 'POST', 'PATCH', 'DELETE'],
    preflightContinue: false,
    optionsSuccessStatus: 204,
    credentials: true,
  });
  app.use(json({ limit: '100mb' }));
  app.setGlobalPrefix('api');
  app.use(compression());
  const prismaService = app.get(PrismaService);
  const data = await prismaService.authorization.findUnique({
    where: { id: 1 },
  });
  if (!data) {
    await prismaService.authorization.createMany({
      data: [
        { name: 'Owner', id: 1 },
        { name: 'Admin', id: 2 },
        { name: 'User', id: 3 },
        { name: 'Left', id: 4 },
        { name: 'Mute', id: 5 },
        { name: 'Banned', id: 6 },
      ],
    });
  }
  const data2 = await prismaService.status.findUnique({
    where: { id: 1 },
  });
  if (!data2) {
    await prismaService.status.createMany({
      data: [
        { status: 'Finished', id: 1 },
        { status: 'Abandoned', id: 2 },
      ],
    });
  }
  await prismaService.enableShutdownHooks(app);
  app.useGlobalPipes(new ValidationPipe({ whitelist: true }));
  const config = new DocumentBuilder()
    .setTitle('ft_trancendence')
    .setDescription('ft_trancendence backend')
    .setVersion('1.0')
    .build();
  const document = SwaggerModule.createDocument(app, config);
  SwaggerModule.setup('api', app, document);
  await app.listen(configService.get<number>('port'), '0.0.0.0');
}
bootstrap();
