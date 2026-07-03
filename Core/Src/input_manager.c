/*
 * This file handles user inputs and delegates the processing to the active screen handler.
 */

#include "input_manager.h"
#include <stddef.h>  // For NULL
#include <stdio.h>
#include "stm32f0xx_hal.h"

// Initialize the input queue
static InputQueue inputQueue = { .head = 0, .tail = 0 };



uint8_t que_status = 0;
// Add an event to the queue
void enqueue_event(InputEvent event) {
  uint8_t next = (inputQueue.head + 1) % INPUT_QUEUE_SIZE;
  if (next != inputQueue.tail) {
    inputQueue.events[inputQueue.head] = event;
    inputQueue.head = next;
    que_status++;
  }
}

uint8_t endo_state;
uint8_t field_status;
// Remove an event from the queue
int dequeue_event(InputEvent *event) {
  if (inputQueue.head == inputQueue.tail) {
    return 0;  // Queue is empty
    que_status = 0;
  }
  *event = inputQueue.events[inputQueue.tail];
  inputQueue.tail = (inputQueue.tail + 1) % INPUT_QUEUE_SIZE;
  return 1;
}

// Process all pending events in the input queue
void process_input_events(void) {
  InputEvent event;
  while (dequeue_event(&event)) {
    handle_input(event.action);
  }
}

int8_t myAction;
InputAction qw;
uint8_t last_value = 1;


//void handle_input(InputAction action) {
//  myAction = action;
//  switch (action) {
//    case INPUT_NW:
//      qw = INPUT_NW;
//      static uint8_t toggle_state2 = 0;
//      if (toggle_state2 == 0 ) {
//        UART_Manager_SendData("@F03#");
//        LED_ControlIntensity(last_value);  // Turn off all intensity LEDs
//        LED_ControlAction(INPUT_NW);       // Turn on ON nw
//        toggle_state2 = 1;
//        field_status = 1;
//      }
//      else {
//              UART_Manager_SendData("@F_0#");
//              LED_ControlIntensity(last_value);  // Turn on 5 intensity LEDs
//              LED_ControlAction(INPUT_NW_off);       // Turn on OFF ENDO
//              toggle_state2 = 0;
//              field_status=0;
//            }
//
//      break;
//    case INPUT_WW:
//      qw = INPUT_WW;
//      static uint8_t toggle_state1 = 0;
//      if (toggle_state1 == 0) {
//        UART_Manager_SendData("@E_1#");
//        LED_ControlIntensity(last_value);  // Turn off all intensity LEDs
//        LED_ControlAction(INPUT_WW);       // Turn on ON ENDO
//        toggle_state1 = 1;
//        endo_state = 1;
//      } else {
//        UART_Manager_SendData("@E_0#");
//        LED_ControlIntensity(last_value);  // Turn on 5 intensity LEDs
//        LED_ControlAction(INPUT_WW_off);       // Turn on OFF ENDO
//        toggle_state1 = 0;
//        endo_state = 0;
//      }
//      break;
//    case INPUT_CW:
//      qw = INPUT_CW;
//      static uint8_t toggle_state3 = 0;
//      if (toggle_state3 == 0 ) {
//        UART_Manager_SendData("@F01#");
//        LED_ControlIntensity(last_value);  // Turn off all intensity LEDs
//        LED_ControlAction(INPUT_CW);       // Turn on ON cw
//        toggle_state3 = 1;
//        field_status = 1;
//      } else if (field_status == 1) {
//          UART_Manager_SendData("@F_0#");
//          LED_ControlIntensity(last_value);  // Turn on 5 intensity LEDs
//          LED_ControlAction(INPUT_CW_off);       // Turn on OFF nw
//          toggle_state3 = 0;
//          field_status = 0;
//      }
//      break;
//    case INPUT_DCR:
//      {
//        if (last_value <= 1) {
//          last_value = 1;
//        } else {
//          last_value--;
//        }
//        char uart_data[8];
//        sprintf(uart_data, "@I0%X#", last_value);
//        if (field_status == 0) {
//          UART_Manager_SendData(uart_data);
//        } else {
//          UART_Manager_SendData();
//        }
//
//        LED_ControlIntensity(last_value);  // Update LED for intensity
//      }
//      break;
//    case INPUT_INC:
//      {
//        if (last_value >= 5) {
//          last_value = 5;
//        } else {
//          last_value++;
//        }
//        char uart_data[8];
//        sprintf(uart_data, "@I0%X#", last_value);
//        if (field_status == 0) {
//          UART_Manager_SendData(uart_data);
//        } else {
//          UART_Manager_SendData();
//        }
//        LED_ControlIntensity(last_value);  // Update LED for intensity
//      }
//      break;
//    case INPUT_TOGGLE:
//      qw = INPUT_TOGGLE;
//      static uint8_t toggle_state = 0;
//      if (toggle_state == 0) {
//        UART_Manager_SendData("@L_0#");
//        LED_ControlIntensity(0);          // Turn off all intensity LEDs
//        LED_ControlAction(INPUT_TOGGLE);  // Turn on ON/OFF LED
//        toggle_state = 1;
//        if (endo_state) {
//          UART_Manager_SendData("@E_1#");
//        }
//      } else {
//        UART_Manager_SendData("@L_1#");
//        LED_ControlIntensity(last_value);  // Turn on 5 intensity LEDs
//        LED_ControlAction(INPUT_TOGGLE_off);   // Turn on ON/OFF LED
//        toggle_state = 0;
//      }
//      break;
//    // Add other cases as necessary...
//    default:
//      break;
//      if (field_status) {
//      }
//  }
//}
//
uint8_t endo_status;

void handle_input(InputAction action) {
  myAction = action;
  switch (action) {
    case INPUT_NW:
      qw = INPUT_NW;
      UART_Manager_SendData("@E_0#");
      endo_status = 0;
      UART_Manager_SendData("@I0:#");
      LED_ControlAction(INPUT_NW);  // Turn on NW LED
      break;
    case INPUT_WW:
      qw = INPUT_WW;
      endo_status = 1;
      UART_Manager_SendData("@E_1#");
      LED_ControlAction(INPUT_WW);  // Turn on WW LED
      break;
    case INPUT_CW:
      qw = INPUT_CW;
      endo_status = 0;
      UART_Manager_SendData("@E_0#");
      UART_Manager_SendData("@I02#");
      LED_ControlAction(INPUT_CW);  // Turn on CW LED
      break;
    case INPUT_DCR:
      {
        if (last_value <= 1) {
          last_value = 1;
        } else {
          last_value--;

          char uart_data[8];
          sprintf(uart_data, "@I0%X#", last_value);
          //                LED_ControlAction(led_off);  // Turn on CW LED
          UART_Manager_SendData(uart_data);
          if (endo_status) {
            LED_ControlAction(led_on);  // Turn on CW LED
          } else {
            LED_ControlAction(led_off);  // Turn on CW LED
          }
          LED_ControlIntensity(last_value);  // Update LED for intensity
        }
        break;
        case INPUT_INC:


          if (last_value >= 5) {
            last_value = 5;
          } else {
            last_value++;
          }
          char uart_data[8];
          sprintf(uart_data, "@I0%X#", last_value);
          UART_Manager_SendData(uart_data);
          if (endo_status == 1) {
            LED_ControlAction(led_on);  // Turn on CW LED
          } else {
            LED_ControlAction(led_off);  // Turn on CW LED
          }

          LED_ControlIntensity(last_value);  // Update LED for intensity
      }
      break;
    case INPUT_TOGGLE:
      qw = INPUT_TOGGLE;
      static uint8_t toggle_state = 0;
      if (toggle_state == 0) {
        UART_Manager_SendData("@L_0#");
        LED_ControlIntensity(0);          // Turn off all intensity LEDs
        LED_ControlIntensity(last_value);  // Turn on 5 intensity LEDs
        LED_ControlAction(INPUT_TOGGLE);  // Turn on ON/OFF LED
        toggle_state = 1;
      } else {
        UART_Manager_SendData("@L_1#");
        LED_ControlIntensity(last_value);     // Turn on 5 intensity LEDs
        LED_ControlAction(INPUT_TOGGLE_off);  // Turn on ON/OFF LED
        toggle_state = 0;
      }
      break;
    // Add other cases as necessary...
    default:
      break;
  }
}
