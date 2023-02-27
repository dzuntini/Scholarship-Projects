import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ChatRoomCreateRoom } from './chatroom-create-room.component';

describe('ChatRoomCreateRoom', () => {
  let component: ChatRoomCreateRoom;
  let fixture: ComponentFixture<ChatRoomCreateRoom>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ChatRoomCreateRoom],
    }).compileComponents();

    fixture = TestBed.createComponent(ChatRoomCreateRoom);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
