import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ChatRoomDeleteRoom } from './chatroom-delete-room.component';

describe('ChatRoomDeleteRoom', () => {
  let component: ChatRoomDeleteRoom;
  let fixture: ComponentFixture<ChatRoomDeleteRoom>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ChatRoomDeleteRoom],
    }).compileComponents();

    fixture = TestBed.createComponent(ChatRoomDeleteRoom);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
