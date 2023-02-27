import { Test, TestingModule } from '@nestjs/testing';
import { AppusersController } from './appusers.controller';
import { AppusersService } from './appusers.service';

describe('AppusersController', () => {
  let controller: AppusersController;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [AppusersController],
      providers: [AppusersService],
    }).compile();

    controller = module.get<AppusersController>(AppusersController);
  });

  it('should be defined', () => {
    expect(controller).toBeDefined();
  });
});
