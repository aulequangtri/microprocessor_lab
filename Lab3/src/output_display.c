/*
 * output_display.c
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */
#include "output_display.h"
#include "pin_map.h"
#include "software_timer.h"

// common-anode, bit0 = a ... bit6 = g, 0 = segment lit
static const uint8_t SEG_CODE[10] = {
  0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10
};

static uint8_t led_buffer[4] = {0, 0, 0, 0};
static uint8_t scan_index = 0;

void display_init(void)
{
  all_leds_off();
  set_digits(0, 0);
  set_digits(2, 0);
  setTimer(TIMER_SCAN, SCAN_PERIOD_MS);
}

void set_digits(uint8_t pos, uint8_t value)
{
  if (pos > 2) return;
  if (value > 99) value = 99;
  led_buffer[pos]     = value / 10;     // tens
  led_buffer[pos + 1] = value % 10;     // ones
}

void display_scan(void)
{
  // 1. all digits off (PNP is active-low: SET = off)
  HAL_GPIO_WritePin(EN_GPIO_Port, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);

  // 2. put this digit's pattern on PB8..PB14 and leave the other pins alone
  SEG_GPIO_Port->ODR = (SEG_GPIO_Port->ODR & ~SEG_MASK)
                     | ((uint32_t)SEG_CODE[led_buffer[scan_index]] << SEG_SHIFT);

  // 3. turn on only this digit (RESET = on)
  HAL_GPIO_WritePin(EN_GPIO_Port, (uint16_t)(EN0_Pin << scan_index), GPIO_PIN_RESET);

  scan_index = (scan_index + 1) % 4;
}

void set_road1(Color_t c)
{
  HAL_GPIO_WritePin(RED1_GPIO_Port,   RED1_Pin,   (c == C_RED)   ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(AMBER1_GPIO_Port, AMBER1_Pin, (c == C_AMBER) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, (c == C_GREEN) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void set_road2(Color_t c)
{
  HAL_GPIO_WritePin(RED2_GPIO_Port,   RED2_Pin,   (c == C_RED)   ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(AMBER2_GPIO_Port, AMBER2_Pin, (c == C_AMBER) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, (c == C_GREEN) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void all_leds_off(void)
{
  set_road1(C_OFF);
  set_road2(C_OFF);
}

void toggle_color(Color_t c)
{
  switch (c) {
    case C_RED:
      HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
      HAL_GPIO_TogglePin(RED2_GPIO_Port, RED2_Pin);
      break;
    case C_AMBER:
      HAL_GPIO_TogglePin(AMBER1_GPIO_Port, AMBER1_Pin);
      HAL_GPIO_TogglePin(AMBER2_GPIO_Port, AMBER2_Pin);
      break;
    case C_GREEN:
      HAL_GPIO_TogglePin(GREEN1_GPIO_Port, GREEN1_Pin);
      HAL_GPIO_TogglePin(GREEN2_GPIO_Port, GREEN2_Pin);
      break;
    default:
      break;
  }
}

