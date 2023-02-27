import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ChatRoomModifyRoom } from './chatroom-modify-room.component';

describe('ChatroomModifyRoomComponent', () => {
  let component: ChatRoomModifyRoom;
  let fixture: ComponentFixture<ChatRoomModifyRoom>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ChatRoomModifyRoom],
    }).compileComponents();

    fixture = TestBed.createComponent(ChatRoomModifyRoom);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
