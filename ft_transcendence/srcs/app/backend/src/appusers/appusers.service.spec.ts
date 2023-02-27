import { Test, TestingModule } from '@nestjs/testing';
import { AppusersService } from './appusers.service';

describe('AppusersService', () => {
  let service: AppusersService;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [AppusersService],
    }).compile();

    service = module.get<AppusersService>(AppusersService);
  });

  it('should be defined', () => {
    expect(service).toBeDefined();
  });
});
