#include "app_main.h"
#include "api_utils.h"
#include "stm32f4xx_hal.h"
#include "hdc1000_driver.h"
#include <stdio.h>


const char * start_msg = "Starting HDC1000 Driver Test...\r\n";
const char * end_msg = "Ending HDC1000 Driver Test...\r\n";

extern I2C_HandleTypeDef hi2c1;


void app_main() {

	char buf[80];

	uartsendString(start_msg);

	hdc_set_iic_handle(&hi2c1);

	sprintf(buf, "manufacturer: %X \r\n", hdc_get_manufacturer_id());
	uartsendString(buf);

	sprintf(buf, "device id: %X \r\n", hdc_get_device_id());
	uartsendString(buf);

	hdc_set_config();

	sprintf(buf, "config: %X \r\n", hdc_get_config());
	uartsendString(buf);


	while (1) {

		// broken for some reason with I2C1 interrupt event
		// broken for DMA and interrupts i2c actions
		// uint32_t current_time = HAL_GetTick();

		HAL_Delay(250);
		hdc_update_data();

		sprintf(buf, "temp: %.2f \r\n", hdc_temperature());
		uartsendString(buf);

		sprintf(buf, "humidity: %.2f \r\n", hdc_humidity());
		uartsendString(buf);
	}

	uartsendString(end_msg);
}


// External Interrupt ISR Handler CallBackFun
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_5) hdc_on_new_data();
}
