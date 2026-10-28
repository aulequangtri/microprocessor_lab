/*
 * input_reading.h
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_
#include "main.h"
#include "software_timer.h"

#define NO_OF_BUTTONS  3

// debounce needs reads at least 10 ms apart
#define BUTTON_READ_PERIOD_MS  ((TIMER_CYCLE) < 10 ? 10 : (TIMER_CYCLE))

void          button_reading(void);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_1s(unsigned char index);


#endif /* INC_INPUT_READING_H_ */
