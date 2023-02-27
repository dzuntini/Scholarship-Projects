import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ProfileGamesComponent } from './profile-games.component';

describe('ProfileGamesComponent', () => {
  let component: ProfileGamesComponent;
  let fixture: ComponentFixture<ProfileGamesComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ProfileGamesComponent],
    }).compileComponents();

    fixture = TestBed.createComponent(ProfileGamesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
