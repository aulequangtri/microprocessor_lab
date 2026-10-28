/*
 * input_reading.c
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */

#include "input_reading.h"
#include "pin_map.h"

#define DURATION_FOR_AUTO_INCREASING  (1000 / BUTTON_READ_PERIOD_MS)
#define BUTTON_IS_PRESSED   GPIO_PIN_RESET
#define BUTTON_IS_RELEASED  GPIO_PIN_SET

static GPIO_TypeDef *buttonPort[NO_OF_BUTTONS] =
    { BUTTON_1_GPIO_Port, BUTTON_2_GPIO_Port, BUTTON_3_GPIO_Port };
static const uint16_t buttonPin[NO_OF_BUTTONS] =
    { BUTTON_1_Pin, BUTTON_2_Pin, BUTTON_3_Pin };

// all buffers start RELEASED (1); otherwise you get a fake press at boot
static volatile GPIO_PinState buttonBuffer[NO_OF_BUTTONS] =
    { GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET };
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS] =
    { GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET };
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS] =
    { GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET };

static volatile uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];

void button_reading(void)
{
  for (uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
    debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
    debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);

    // two equal reads in a row = a stable value
    if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
      buttonBuffer[i] = debounceButtonBuffer1[i];

    if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
      if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING)
        counterForButtonPress1s[i]++;
      else
        flagForButtonPress1s[i] = 1;      // held for 1 second
    } else {
      counterForButtonPress1s[i] = 0;
      flagForButtonPress1s[i] = 0;
    }
  }
}

unsigned char is_button_pressed(unsigned char index)
{
  if (index >= NO_OF_BUTTONS) return 0;
  return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(unsigned char index)
{
  if (index >= NO_OF_BUTTONS) return 0;
  return (flagForButtonPress1s[index] == 1);
}
