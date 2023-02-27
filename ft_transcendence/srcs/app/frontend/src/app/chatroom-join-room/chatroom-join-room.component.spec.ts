import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ChatRoomJoinRoom } from './chatroom-join-room.component';

describe('ChatRoomJoinRoom', () => {
  let component: ChatRoomJoinRoom;
  let fixture: ComponentFixture<ChatRoomJoinRoom>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ChatRoomJoinRoom],
    }).compileComponents();

    fixture = TestBed.createComponent(ChatRoomJoinRoom);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
