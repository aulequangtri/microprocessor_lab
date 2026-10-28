/*
 * timer.c
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */


#include "software_timer.h"

static volatile int     timerCounter[NO_OF_TIMERS];
static volatile uint8_t timerFlag[NO_OF_TIMERS];

void setTimer(int index, int duration_ms)
{
  int ticks = (duration_ms + TIMER_CYCLE / 2) / TIMER_CYCLE;   // round to nearest tick
  if (ticks < 1) ticks = 1;
  timerCounter[index] = ticks;
  timerFlag[index] = 0;
}

uint8_t isTimerExpired(int index)
{
  if (timerFlag[index]) {
    timerFlag[index] = 0;
    return 1;
  }
  return 0;
}

void timerRun(void)
{
  for (int i = 0; i < NO_OF_TIMERS; i++) {
    if (timerCounter[i] > 0) {
      timerCounter[i]--;
      if (timerCounter[i] == 0) timerFlag[i] = 1;
    }
  }
}
