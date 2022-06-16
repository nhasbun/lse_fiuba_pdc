#include "hdc1000_driver.h"


#define HDC_DEFAULT_ADD 0x80
#define TEMP_REGISTER 0x00
#define HUMIDITY_REGISTER 0x01
#define CONFIGURATION_REGISTER 0x02
#define MANUFACTURER_REGISTER 0xfe
#define DEVICE_REGISTER 0xff


/**
 * Specific port functions
 */
extern void set_iic_handle(void * handle);
extern uint16_t read_register(uint8_t device_add, uint8_t device_reg);
extern void write_register(uint8_t device_add, uint8_t device_reg, uint16_t value);
extern void read_burst(uint8_t device_add, uint8_t num_bytes, uint8_t * data);
extern void write_byte(uint8_t device_add, uint8_t value);


static uint8_t device_add = HDC_DEFAULT_ADD;
static uint8_t pending_data = 0;
static uint8_t buffer[4] = {0};


void hdc_set_iic_handle(void * iic_handle) {
	set_iic_handle(iic_handle);
}


void hdc_set_device_address(uint8_t add) {
	device_add = add;
}


void hdc_set_config() {
	write_register(device_add, CONFIGURATION_REGISTER, 0x1000);
}


uint16_t hdc_get_config() {
	return read_register(device_add, CONFIGURATION_REGISTER);
}


uint16_t hdc_get_manufacturer_id() {
	return read_register(device_add, MANUFACTURER_REGISTER);
}

uint16_t hdc_get_device_id() {
	return read_register(device_add, DEVICE_REGISTER);
}

void hdc_on_new_data() {
	pending_data = 1;
}

void hdc_update_data() {

	if (pending_data) {
		read_burst(device_add, 4, buffer);
		pending_data = 0;
	}

	// Request new data
	write_byte(device_add, TEMP_REGISTER);
}

float hdc_temperature() {
	uint16_t reading = (buffer[0] << 8) + buffer[1];
	return ((float) reading) * 165.0f / ((float) (1 << 16)) - 40.0f;
}

float hdc_humidity() {
	uint16_t reading = (buffer[2] << 8) + buffer[3];
	return ((float) reading) * 100.0f / ((float) (1 << 16));
}
