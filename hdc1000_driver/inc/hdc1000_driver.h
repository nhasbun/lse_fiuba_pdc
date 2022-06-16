#pragma once

#include <stdint.h>

/**
 * Before using this driver a i2c object handler should be indicated.
 */
void hdc_set_iic_handle(void * iic_handle);

void hdc_set_device_address(uint8_t add);
void hdc_set_config();
uint16_t hdc_get_config();
uint16_t hdc_get_manufacturer_id();
uint16_t hdc_get_device_id();
void hdc_on_new_data();
void hdc_update_data();
float hdc_temperature();
float hdc_humidity();
