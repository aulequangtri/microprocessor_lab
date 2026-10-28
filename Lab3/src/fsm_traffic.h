/*
 * fsm_traffic.h
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */

#ifndef INC_FSM_TRAFFIC_H_
#define INC_FSM_TRAFFIC_H_

#include <stdint.h>

typedef enum { MODE_NORMAL = 1, MODE_RED, MODE_AMBER, MODE_GREEN } Mode_t;

void    fsm_init(void);
void    fsm_run(void);
Mode_t  get_mode(void);

// used by normal mode in Exercise 10
uint8_t get_red_time(void);
uint8_t get_amber_time(void);
uint8_t get_green_time(void);

#endif
