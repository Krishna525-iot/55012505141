#include "uart_manager.h"
#include <string.h>  // For strlen

// UART data send function

uint8_t buffer[5];
void UART_Manager_SendData(const char *data) {

	strcpy(buffer, data);
    HAL_UART_Transmit(&huart1, (uint8_t*)data, strlen(data), HAL_MAX_DELAY);
}
