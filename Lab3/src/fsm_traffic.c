/*
 * fsm_traffic.c
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */
#include "fsm_traffic.h"
#include "input_processing.h"
#include "output_display.h"
#include "software_timer.h"
#include "main.h"

#define BLINK_PERIOD_MS  250      // toggle every 250 ms = 2 Hz
#define MIN_TIME         1
#define MAX_TIME         99

static Mode_t mode = MODE_NORMAL;

// saved durations in seconds, rule: red = amber + green
static uint8_t red_time   = 5;
static uint8_t amber_time = 2;
static uint8_t green_time = 3;

static uint8_t temp_value = 0;    // value being edited, not saved yet

static Color_t edit_color(Mode_t m)
{
  switch (m) {
    case MODE_RED:   return C_RED;
    case MODE_AMBER: return C_AMBER;
    case MODE_GREEN: return C_GREEN;
    default:         return C_OFF;
  }
}

static uint8_t saved_value(Mode_t m)
{
  switch (m) {
    case MODE_RED:   return red_time;
    case MODE_AMBER: return amber_time;
    case MODE_GREEN: return green_time;
    default:         return 0;
  }
}

// returns 1 if the value was accepted, 0 if rejected
static uint8_t apply_value(Mode_t m, uint8_t v)
{
  switch (m) {
    case MODE_RED:                              // Exercise 7
      if (v <= amber_time) return 0;
      red_time   = v;
      green_time = v - amber_time;
      return 1;

    case MODE_AMBER:                            // Exercise 8
      if (v >= red_time) return 0;
      amber_time = v;
      green_time = red_time - amber_time;
      return 1;

    case MODE_GREEN:                            // Exercise 9
      if (amber_time + v > MAX_TIME) return 0;
      green_time = v;
      red_time   = amber_time + v;
      return 1;

    default:
      return 0;
  }
}
static uint8_t phase = 0;        // 0..3, see the traffic FSM from Exercise 1
static uint8_t remaining = 0;    // seconds left in the current phase

static uint8_t phase_duration(uint8_t p)
{
  return (p % 2 == 0) ? green_time : amber_time;   // phases 0,2 green; 1,3 amber
}

static void apply_phase(void)
{
  switch (phase) {
    case 0: set_road1(C_GREEN); set_road2(C_RED);   break;
    case 1: set_road1(C_AMBER); set_road2(C_RED);   break;
    case 2: set_road1(C_RED);   set_road2(C_GREEN); break;
    default: set_road1(C_RED);  set_road2(C_AMBER); break;
  }
}

static void update_countdown(void)
{
  uint8_t r1, r2;
  switch (phase) {
    case 0:  r1 = remaining;              r2 = remaining + amber_time; break;
    case 2:  r1 = remaining + amber_time; r2 = remaining;              break;
    default: r1 = remaining;              r2 = remaining;              break;
  }
  set_digits(0, r1);     // road 1
  set_digits(2, r2);     // road 2
}

static void normal_init(void)
{
  phase = 0;
  remaining = green_time;
  apply_phase();
  update_countdown();
  setTimer(TIMER_SECOND, 1000);
}

static void run_normal(void)
{
  if (isTimerExpired(TIMER_SECOND)) {
    setTimer(TIMER_SECOND, 1000);
    if (--remaining == 0) {
      phase = (phase + 1) % 4;
      remaining = phase_duration(phase);
      apply_phase();
    }
    update_countdown();
  }
}
static void enter_mode(Mode_t m)
{
  mode = m;
  all_leds_off();

  if (m == MODE_NORMAL) {
    normal_init();                       // countdown digits come from here
  } else {
    set_digits(2, (uint8_t)m);           // mode number on digits 2 and 3
    temp_value = saved_value(m);
    set_digits(0, temp_value);           // value on digits 0 and 1
    setTimer(TIMER_BLINK, BLINK_PERIOD_MS);
  }
}

void fsm_init(void)
{
  enter_mode(MODE_NORMAL);
}

void fsm_run(void)
{
  // poll every button exactly once per loop
  uint8_t evMode = button_event(0, 0);   // button 1: change mode
  uint8_t evInc  = button_event(1, 1);   // button 2: increase, auto repeat
  uint8_t evSet  = button_event(2, 0);   // button 3: set

  if (evMode) {
    enter_mode((mode == MODE_GREEN) ? MODE_NORMAL : (Mode_t)(mode + 1));
    return;
  }

  if (mode == MODE_NORMAL) {
      run_normal();
      return;
    } // normal run comes in Exercise 10

  if (evInc) {
    temp_value = (temp_value >= MAX_TIME) ? MIN_TIME : (uint8_t)(temp_value + 1);
    set_digits(0, temp_value);
  }

  if (evSet) {
    if (!apply_value(mode, temp_value)) {
      temp_value = saved_value(mode);    // rejected: go back to the saved value
    }
    set_digits(0, temp_value);
  }

  if (isTimerExpired(TIMER_BLINK)) {
    setTimer(TIMER_BLINK, BLINK_PERIOD_MS);
    toggle_color(edit_color(mode));
  }
}

Mode_t  get_mode(void)       { return mode; }
uint8_t get_red_time(void)   { return red_time; }
uint8_t get_amber_time(void) { return amber_time; }
uint8_t get_green_time(void) { return green_time; }
