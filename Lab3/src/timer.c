/*
 * timer.c
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */


#include "main.h"
#include "software_timer.h"
#include "input_reading.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static int divider = 0;
  if (htim->Instance == TIM2) {
    timerRun();
    if (++divider >= BUTTON_READ_PERIOD_MS / TIMER_CYCLE) {
      divider = 0;
      button_reading();
    }
  }
}
