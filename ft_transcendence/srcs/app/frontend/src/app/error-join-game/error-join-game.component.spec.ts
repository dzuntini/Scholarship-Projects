import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ErrorJoinGameComponent } from './error-join-game.component';

describe('ErrorJoinGameComponent', () => {
  let component: ErrorJoinGameComponent;
  let fixture: ComponentFixture<ErrorJoinGameComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ErrorJoinGameComponent],
    }).compileComponents();

    fixture = TestBed.createComponent(ErrorJoinGameComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
