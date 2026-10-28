/*
 * input_processing.h
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include <stdint.h>

// returns 1 once per press, and again every 500 ms while held
// longer than 1 s (only if repeat == 1)
uint8_t button_event(uint8_t index, uint8_t repeat);

#endif
