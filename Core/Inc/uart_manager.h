#ifndef UART_MANAGER_H
#define UART_MANAGER_H

#include "stm32f0xx_hal.h"  // Include HAL header for UART, change based on your MCU

// UART instance declaration (modify as per your hardware configuration)
extern UART_HandleTypeDef huart1;  // For example, using UART1

// Function to send data over UART
void UART_Manager_SendData(const char *data);

#endif // UART_MANAGER_H
