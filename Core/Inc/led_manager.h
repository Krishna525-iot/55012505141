#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include "stm32f0xx_hal.h"  // Include HAL header for GPIO, modify based on your MCU
#include "input_manager.h"
// Define LED GPIO pins for intensity levels (LEDs 1-5)
//#define D1_PIN         GPIO_PIN_6
//#define LED_1_GPIO_PORT   GPIOA
//#define LED_2_PIN         GPIO_PIN_7
//#define LED_2_GPIO_PORT   GPIOA
//#define LED_3_PIN         GPIO_PIN_0
//#define LED_3_GPIO_PORT   GPIOB
//#define LED_4_PIN         GPIO_PIN_1
//#define LED_4_GPIO_PORT   GPIOB
//#define LED_5_PIN         GPIO_PIN_8
//#define LED_5_GPIO_PORT   GPIOA
//
//// Define LED GPIO pins for CW, WW, NW, and ON/OFF
//#define D1_PIN        GPIO_PIN_12
//#define D1_GPIO_PORT  GPIOA
//#define D3_PIN        GPIO_PIN_10
//#define LED_WW_GPIO_PORT  GPIOA
//#define LED_NW_PIN        GPIO_PIN_9
//#define LED_NW_GPIO_PORT  GPIOA
//#define D2_PIN    GPIO_PIN_11
//#define D2_GPIO_PORT GPIOA




// LED control functions

void LED_Init(void);                    // Initialize LED GPIO pins
void LED_ControlIntensity(uint8_t level);  // Control intensity level LEDs
void LED_ControlAction(InputAction action);    // Control CW, WW, NW LEDs
void system_init(void);

#endif // LED_MANAGER_H
