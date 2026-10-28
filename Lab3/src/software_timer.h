/*
 * timer.h
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include <stdint.h>

#define TIMER_CYCLE    10     // ms, MUST equal the TIM2 interrupt period in CubeMX

#define TIMER_BLINK    0
#define TIMER_SECOND   1
#define TIMER_SCAN     2
#define TIMER_REPEAT   3      // uses 3, 4, 5 (one per button)
#define NO_OF_TIMERS   6

void    setTimer(int index, int duration_ms);
uint8_t isTimerExpired(int index);
void    timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
