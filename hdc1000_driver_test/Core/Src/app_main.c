#include "app_main.h"
#include "api_utils.h"
#include "stm32f4xx_hal.h"
#include "hdc1000_driver.h"
#include <stdio.h>


const char * start_msg = "Starting HDC1000 Driver Test...\r\n";
const char * end_msg = "Ending HDC1000 Driver Test...\r\n";

uint8_t hdc_add = 0x80;
uint8_t temp_register = 0x00;
uint8_t hum_register = 0x01;
uint8_t config_register = 0x02;
uint8_t manufacturer_register = 0xfe;
uint8_t device_id_register = 0xff;
HAL_StatusTypeDef result;

extern I2C_HandleTypeDef hi2c1;


void on_new_interrupt();


void app_main() {

	char buf[80];
	uint8_t buffer[4];
	uint16_t reading;

	uartsendString(start_msg);

	result = HAL_I2C_Master_Transmit(&hi2c1, hdc_add, &manufacturer_register, 1, 1000);
	result = HAL_I2C_Master_Receive(&hi2c1, hdc_add, buffer, 2, 100);

	reading = (buffer[0] << 8) + buffer[1];

	sprintf(buf, "manufacturer: %X \r\n", reading);
	uartsendString(buf);

	result = HAL_I2C_Master_Transmit(&hi2c1, hdc_add, &device_id_register, 1, 1000);
	result = HAL_I2C_Master_Receive(&hi2c1, hdc_add, buffer, 2, 100);

	reading = (buffer[0] << 8) + buffer[1];

	sprintf(buf, "device id: %X \r\n", reading);
	uartsendString(buf);

	result = HAL_I2C_Master_Transmit(&hi2c1, hdc_add, &config_register, 1, 1000);
	result = HAL_I2C_Master_Receive(&hi2c1, hdc_add, buffer, 2, 100);

	reading = (buffer[0] << 8) + buffer[1];

	sprintf(buf, "config register: %X \r\n", reading);
	uartsendString(buf);

	result = HAL_I2C_Master_Transmit(&hi2c1, hdc_add, &temp_register, 1, 1000);
	result = HAL_I2C_Master_Receive(&hi2c1, hdc_add, buffer, 4, 100);

	uint32_t reading32 = (buffer[0] << 8) + buffer[1];
	uint32_t reading32_2 = (buffer[2] << 8) + buffer[3];

	float temperature = ((float) reading32) * 165.0f / ((float) (1 << 16)) - 40.0f;
	float humidity = ((float) reading32_2) * 100.0f / ((float) (1 << 16));

	sprintf(buf, "temperature: %.2f \r\n", temperature);
	uartsendString(buf);

	sprintf(buf, "humidity: %.2f \r\n", humidity);
	uartsendString(buf);


	// write data register to 0x00 to trigger new capture
	uint8_t data[3];

	data[0] = 0x0;
	data[1] = 0x0;
	data[2] = 0x0;

	result = HAL_I2C_Master_Transmit(&hi2c1, hdc_add, data, 3, 1000);

	uartsendString(end_msg);
}


void on_new_interrupt() {

	static uint32_t counter = 0;
	counter++;
}


// External Interrupt ISR Handler CallBackFun
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_5) on_new_interrupt();
}
