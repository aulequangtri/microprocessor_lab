/*
 * pin_map.h
 *
 *  Created on: Oct 22, 2026
 *      Author: tri
 */

#ifndef INC_PIN_MAP_H_
#define INC_PIN_MAP_H_

#include "main.h"

#define BUTTON_1_GPIO_Port  GPIOB
#define BUTTON_1_Pin        GPIO_PIN_0
#define BUTTON_2_GPIO_Port  GPIOB
#define BUTTON_2_Pin        GPIO_PIN_1
#define BUTTON_3_GPIO_Port  GPIOB
#define BUTTON_3_Pin        GPIO_PIN_2

#define RED1_GPIO_Port      GPIOA
#define RED1_Pin            GPIO_PIN_0
#define AMBER1_GPIO_Port    GPIOA
#define AMBER1_Pin          GPIO_PIN_1
#define GREEN1_GPIO_Port    GPIOA
#define GREEN1_Pin          GPIO_PIN_2
#define RED2_GPIO_Port      GPIOA
#define RED2_Pin            GPIO_PIN_3
#define AMBER2_GPIO_Port    GPIOA
#define AMBER2_Pin          GPIO_PIN_4
#define GREEN2_GPIO_Port    GPIOA
#define GREEN2_Pin          GPIO_PIN_5

#define EN0_Pin             GPIO_PIN_6
#define EN1_Pin             GPIO_PIN_7
#define EN2_Pin             GPIO_PIN_8
#define EN3_Pin             GPIO_PIN_9
#define EN_GPIO_Port        GPIOA

#define SEG_GPIO_Port       GPIOB
#define SEG_SHIFT           8
#define SEG_MASK            (0x7FUL << SEG_SHIFT)

#endif
