#include "stm32f4xx_hal.h"


static I2C_HandleTypeDef iic;
static HAL_StatusTypeDef op_status;


void _set_iic_handle(void * handle) {

	iic = *((I2C_HandleTypeDef*) handle);
}


uint16_t read_register(uint8_t device_add, uint8_t device_reg) {
	uint8_t buffer[2];
	op_status = HAL_I2C_Master_Transmit(&iic, device_add, &device_reg, 1, 1000);
	op_status = HAL_I2C_Master_Receive(&iic, device_add, buffer, 2, 100);
	return (buffer[0] << 8) + buffer[1];
}
