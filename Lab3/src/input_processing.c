/*
 * input_processing.c
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */


#include "input_processing.h"
#include "input_reading.h"
#include "software_timer.h"

enum ButtonState {
  BUTTON_RELEASED,
  BUTTON_PRESSED,
  BUTTON_PRESSED_MORE_THAN_1_SECOND
};

uint8_t button_event(uint8_t index, uint8_t repeat)
{
  static enum ButtonState state[NO_OF_BUTTONS];   // starts at BUTTON_RELEASED
  uint8_t event = 0;

  switch (state[index]) {
    case BUTTON_RELEASED:
      if (is_button_pressed(index)) {
        state[index] = BUTTON_PRESSED;
        event = 1;                                 // action on the first press
      }
      break;

    case BUTTON_PRESSED:
      if (!is_button_pressed(index)) {
        state[index] = BUTTON_RELEASED;
      } else if (is_button_pressed_1s(index)) {
        state[index] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
        setTimer(TIMER_REPEAT + index, 500);
      }
      break;

    case BUTTON_PRESSED_MORE_THAN_1_SECOND:
      if (!is_button_pressed(index)) {
        state[index] = BUTTON_RELEASED;
      } else if (repeat && isTimerExpired(TIMER_REPEAT + index)) {
        event = 1;                                 // auto repeat
        setTimer(TIMER_REPEAT + index, 500);
      }
      break;
  }
  return event;
}
