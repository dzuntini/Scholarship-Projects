import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ChatroomJoinPasswordComponent } from './chatroom-join-password.component';

describe('ChatroomJoinPasswordComponent', () => {
  let component: ChatroomJoinPasswordComponent;
  let fixture: ComponentFixture<ChatroomJoinPasswordComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ChatroomJoinPasswordComponent],
    }).compileComponents();

    fixture = TestBed.createComponent(ChatroomJoinPasswordComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
