#include "led_manager.h"
#include "main.h"  // Include HAL for GPIO
#include "input_manager.h"

// Initialize LED GPIO pins
//void LED_Init(void) {
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//    // Enable clock for GPIOA and GPIOB (adjust according to your MCU)
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//
//    // Initialize pins for intensity LEDs (LED1-LED5)
//    GPIO_InitStruct.Pin = LED_1_PIN | LED_2_PIN | LED_3_PIN | LED_4_PIN | LED_5_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);  // Use GPIOA for LEDs 1-5, GPIOB for LED 3 and LED 4
//
//    // Initialize pins for CW, WW, NW, and ON/OFF LEDs
//    GPIO_InitStruct.Pin = LED_CW_PIN | LED_WW_PIN | LED_NW_PIN | LED_ON_OFF_PIN;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);  // Use GPIOA for CW, WW, NW, and ON/OFF LEDs
//}

// Control intensity level LEDs
// Control intensity level LEDs (LED1-LED5)
void system_init() {
  HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(NW_GPIO_Port, NW_Pin, GPIO_PIN_SET);  // Turn off CW LED
  HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);  // Turn on WW LED
  HAL_GPIO_WritePin(WW_GPIO_Port, WW_Pin, GPIO_PIN_SET);  // Turn off NW LED
  HAL_GPIO_WritePin(ON_OFF_GPIO_Port, ON_OFF_Pin, GPIO_PIN_SET);

  UART_Manager_SendData("@C05#");
  HAL_Delay(20);
  UART_Manager_SendData("@L_1#");
  HAL_Delay(20);
  UART_Manager_SendData("@I01#");
  HAL_Delay(20);
}




static int previous_level = 0;
void LED_ControlIntensity(uint8_t level) {
  // Array of GPIO ports and pins
  GPIO_TypeDef* gpio_ports[] = { D1_GPIO_Port, D2_GPIO_Port, D3_GPIO_Port, D4_GPIO_Port, D5_GPIO_Port };
  uint16_t gpio_pins[] = { D1_Pin, D2_Pin, D3_Pin, D4_Pin, D5_Pin };

  // Check if the level is increasing or decreasing
  if (level > previous_level) {
    // Increasing intensity: turn on LEDs up to the current level
    for (int i = previous_level; i < level; i++) {
      HAL_GPIO_WritePin(gpio_ports[i], gpio_pins[i], GPIO_PIN_RESET);  // Turn on LED
    }
  } else if (level < previous_level) {
    // Decreasing intensity: turn off LEDs from the last turned-on one
    for (int i = previous_level - 1; i >= level; i--) {
      HAL_GPIO_WritePin(gpio_ports[i], gpio_pins[i], GPIO_PIN_SET);  // Turn off LED
    }
  }

  // Update the previous level
  previous_level = level;
}

InputAction LED_STATUS;
// Control CW, WW, NW, and ON/OFF LEDs
void LED_ControlAction(InputAction action) {
  LED_STATUS = action;
  switch (action) {
    case INPUT_CW:                                              // CW (Control CW LED)
      HAL_GPIO_WritePin(NW_GPIO_Port, NW_Pin, GPIO_PIN_SET);    // Turn off CW LED
      HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);  // Turn on WW LED
      HAL_GPIO_WritePin(WW_GPIO_Port, WW_Pin, GPIO_PIN_SET);    // Turn off NW LED
      break;
    case INPUT_WW:                                              // WW (Control WW LED)
      HAL_GPIO_WritePin(NW_GPIO_Port, NW_Pin, GPIO_PIN_SET);    // Turn off CW LED
      HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);    // Turn on WW LED
      HAL_GPIO_WritePin(WW_GPIO_Port, WW_Pin, GPIO_PIN_RESET);  // Turn off NW LED
      break;
    case INPUT_NW:                                              // NW (Control NW LED)
      HAL_GPIO_WritePin(NW_GPIO_Port, NW_Pin, GPIO_PIN_RESET);  // Turn off CW LED
      HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);    // Turn on WW LED
      HAL_GPIO_WritePin(WW_GPIO_Port, WW_Pin, GPIO_PIN_SET);    // Turn off NW LED
      break;
    case INPUT_TOGGLE:                                                  // ON/OFF (Control ON/OFF LED)
      HAL_GPIO_WritePin(ON_OFF_GPIO_Port, ON_OFF_Pin, GPIO_PIN_RESET);  // Turn on ON/OFF LED

      break;
    case INPUT_CW_off:
      HAL_GPIO_WritePin(NW_GPIO_Port, NW_Pin, GPIO_PIN_SET);  // Turn off CW LED
      HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);  // Turn on WW LED
      HAL_GPIO_WritePin(WW_GPIO_Port, WW_Pin, GPIO_PIN_SET);  // Turn off NW LED
      break;
    case INPUT_WW_off:
      HAL_GPIO_WritePin(NW_GPIO_Port, NW_Pin, GPIO_PIN_SET);  // Turn off CW LED
      HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);  // Turn on WW LED
      HAL_GPIO_WritePin(WW_GPIO_Port, WW_Pin, GPIO_PIN_SET);  // Turn off NW LED
      break;
    case INPUT_NW_off:
      HAL_GPIO_WritePin(NW_GPIO_Port, NW_Pin, GPIO_PIN_SET);  // Turn off CW LED
      HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);  // Turn on WW LED
      HAL_GPIO_WritePin(WW_GPIO_Port, WW_Pin, GPIO_PIN_SET);  // Turn off NW LED
      break;
    case INPUT_TOGGLE_off:
      HAL_GPIO_WritePin(ON_OFF_GPIO_Port, ON_OFF_Pin, GPIO_PIN_SET);  // Turn on ON/OFF LED
      break;
    case led_off:
      HAL_GPIO_WritePin(NW_GPIO_Port, NW_Pin, GPIO_PIN_SET);  // Turn off CW LED
      HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);  // Turn on WW LED
      HAL_GPIO_WritePin(WW_GPIO_Port, WW_Pin, GPIO_PIN_SET);  // Turn off NW LED
      break;
    case led_on:
      HAL_GPIO_WritePin(NW_GPIO_Port, NW_Pin, GPIO_PIN_SET);    // Turn off CW LED
      HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);    // Turn on WW LED
      HAL_GPIO_WritePin(WW_GPIO_Port, WW_Pin, GPIO_PIN_RESET);  // Turn off NW LED
      break;
    default:
      // Default case if action is not recognized
      break;
  }
}
