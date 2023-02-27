import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ProfileFriendlistComponent } from './profile-friendlist.component';

describe('ProfileFriendlistComponent', () => {
  let component: ProfileFriendlistComponent;
  let fixture: ComponentFixture<ProfileFriendlistComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ProfileFriendlistComponent],
    }).compileComponents();

    fixture = TestBed.createComponent(ProfileFriendlistComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
