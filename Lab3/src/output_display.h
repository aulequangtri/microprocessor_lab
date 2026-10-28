/*
 * output_display.h
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */

#ifndef INC_OUTPUT_DISPLAY_H_
#define INC_OUTPUT_DISPLAY_H_

#include <stdint.h>

#define SCAN_PERIOD_MS  5      // time between two digits

typedef enum { C_OFF, C_RED, C_AMBER, C_GREEN } Color_t;

void display_init(void);
void display_scan(void);                    // call every SCAN_PERIOD_MS
void set_digits(uint8_t pos, uint8_t value); // pos 0 = digits 0,1   pos 2 = digits 2,3
void set_road1(Color_t c);
void set_road2(Color_t c);
void all_leds_off(void);
void toggle_color(Color_t c);               // toggles that color on both roads

#endif
