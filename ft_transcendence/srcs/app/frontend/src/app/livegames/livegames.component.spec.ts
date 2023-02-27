import { ComponentFixture, TestBed } from '@angular/core/testing';

import { LivegamesComponent } from './livegames.component';

describe('LivegamesComponent', () => {
  let component: LivegamesComponent;
  let fixture: ComponentFixture<LivegamesComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [LivegamesComponent],
    }).compileComponents();

    fixture = TestBed.createComponent(LivegamesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
