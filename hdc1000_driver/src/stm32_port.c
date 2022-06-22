/**
 * @file stm32_port.c
 * @brief Wrapper for stm32f platform specifics.
 */

#include "stm32f4xx_hal.h"


static I2C_HandleTypeDef iic;
static HAL_StatusTypeDef op_status1;
static HAL_StatusTypeDef op_status2;


void set_iic_handle(void * handle) {

	iic = *((I2C_HandleTypeDef*) handle);
}


uint16_t read_register(uint8_t device_add, uint8_t device_reg) {

	uint8_t buffer[2] = {0};

	op_status1 = HAL_I2C_Master_Transmit(&iic, device_add << 1, &device_reg, 1, 1000);
	op_status2 = HAL_I2C_Master_Receive(&iic, device_add << 1, buffer, 2, 100);

	return (buffer[0] << 8) + buffer[1];
}

void write_register(uint8_t device_add, uint8_t device_reg, uint16_t value) {
	uint8_t data[3];

	data[0] = device_reg;
	data[1] = (uint8_t) (value >> 8);
	data[2] = (uint8_t) value;

	op_status1 = HAL_I2C_Master_Transmit(&iic, device_add << 1, data, 3, 100);
}


void read_burst(uint8_t device_add, uint8_t num_bytes, uint8_t * data) {

	op_status1 = HAL_I2C_Master_Receive(&iic, device_add << 1, data, num_bytes, 1000);
}


void write_byte(uint8_t device_add, uint8_t value) {

	op_status1 = HAL_I2C_Master_Transmit(&iic, device_add << 1, &value, 1, 100);
}



