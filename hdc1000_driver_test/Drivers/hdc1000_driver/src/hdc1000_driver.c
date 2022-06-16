#include "hdc1000_driver.h"


#define HDC_DEFAULT_ADD 0x80
#define MANUFACTURER_REGISTER 0xfe
#define DEVICE_REGISTER 0xff


/**
 * Specific port functions
 */
extern void _set_iic_handle(void * handle);
extern uint16_t read_register(uint8_t device_add, uint8_t device_reg);


static uint8_t device_add = HDC_DEFAULT_ADD;


void set_iic_handle(void * iic_handle) {
	_set_iic_handle(iic_handle);
}


void set_device_address(uint8_t add) {
	device_add = add;
}


uint16_t get_manufacturer_id() {
	return read_register(device_add, MANUFACTURER_REGISTER);
}

uint16_t get_device_id() {
	return read_register(device_add, DEVICE_REGISTER);
}
