#include "api_utils.h"
#include "stm32f4xx_hal.h"
#include <string.h>


extern UART_HandleTypeDef huart3;


void uartsendString(const char * pstring) {
	HAL_UART_Transmit(&huart3, (uint8_t*) pstring, strlen(pstring), 1000);
}
