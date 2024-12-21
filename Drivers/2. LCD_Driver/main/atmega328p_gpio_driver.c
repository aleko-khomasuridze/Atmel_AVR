#include "atmega328p_gpio_driver.h"

void GPIO_init(GPIOPin pin, GPIODirection direction) {
    if (direction == GPIO_DIR_OUTPUT) {
        *(pin.ddr) |= (1 << pin.pinNumber);  // Set pin as output
    } else {
        *(pin.ddr) &= ~(1 << pin.pinNumber);  // Set pin as input
    }
}

GPIOState GPIO_read(GPIOPin pin) {
    if (*(pin.pin) & (1 << pin.pinNumber)) {
        return GPIO_HIGH;
    } else {
        return GPIO_LOW;
    }
}

void GPIO_write(GPIOPin pin, GPIOState state) {
    if (state == GPIO_HIGH) {
        *(pin.port) |= (1 << pin.pinNumber);  // Set pin high
    } else {
        *(pin.port) &= ~(1 << pin.pinNumber);  // Set pin low
    }
}

void GPIO_toggle(GPIOPin pin) {
    *(pin.port) ^= (1 << pin.pinNumber);  // Toggle the pin state
}

void GPIO_writePort(volatile uint8_t *port, uint8_t state) {
    *port = state;  // Write state to the entire port
}
