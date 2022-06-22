/**
 * @file hdc1000_driver.h
 * @brief API for hdc1000 driver.
 *
 * Driver expect a valid i2c communication channel already configured. Also hdc1000
 * has a DRDYn pin which is expected to be associated with hdc_on_new_data() callback function.
 */

#pragma once

#include <stdint.h>

/**
 * Before using this driver a i2c object handler should be indicated.
 *
 * For platforms without handlers a null pointer could be used.
 */
void hdc_set_iic_handle(void * iic_handle);

/**
 * Change device address (default 0x40)
 */
void hdc_set_device_address(uint8_t add);

/**
 * Setting configuration register needed for this driver to work accordingly.
 */
void hdc_set_config();

/**
 * Checking configuration register on HDC1000. Driver needs a value of 0x1000 here.
 */
uint16_t hdc_get_config();

/**
 * Get manufacturer id register.
 *
 * Useful for verifying hardware and testing communications.
 * Expected value of 0x5449 (Texas Instruments ID).
 */
uint16_t hdc_get_manufacturer_id();

/**
 * Get device id register. Useful for verifying hardware and testing communications.
 *
 * Expected value of 0x1000 (HDC1000 ID).
 */
uint16_t hdc_get_device_id();

/**
 * Callback function for data ready pin.
 *
 * Internally raise a flag for a pending data operation.
 */
void hdc_on_new_data();

/**
 * If pending data read both temp and humidity info. Request new measures as final action.
 *
 * Method is expected to be polled with period of ~20ms or more.
 */
void hdc_update_data();

/**
 * Delivers last value of temperature acquired [celsius].
 */
float hdc_temperature();

/**
 * Delivers last value of RH acquired [RH%].
 */
float hdc_humidity();
