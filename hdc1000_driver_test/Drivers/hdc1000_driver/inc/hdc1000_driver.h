#pragma once

#include <stdint.h>

/**
 * Before using this driver a i2c object handler should be indicated.
 */
void set_iic_handle(void * iic_handle);

void set_device_address(uint8_t add);
uint16_t get_manufacturer_id();
uint16_t get_device_id();
