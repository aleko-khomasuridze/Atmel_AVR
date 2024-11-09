#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <avr/io.h>
#include <stdint.h>

// GPIO Pin Direction
typedef enum {
    GPIO_DIR_INPUT,
    GPIO_DIR_OUTPUT
} GPIODirection;

// GPIO Pin State
typedef enum {
    GPIO_LOW,
    GPIO_HIGH
} GPIOState;

// GPIO Port and Pin configuration
typedef struct {
    volatile uint8_t *ddr;  // Data Direction Register address
    volatile uint8_t *port; // Port Output Register address
    volatile uint8_t *pin;  // Pin Input Register address
    uint8_t pinNumber;      // Pin number on the port
} GPIOPin;

// Function prototypes
void gpio_init(GPIOPin pin, GPIODirection direction);
GPIOState gpio_read(GPIOPin pin);
void gpio_write(GPIOPin pin, GPIOState state);
void gpio_toggle(GPIOPin pin);
void gpio_write_port(volatile uint8_t *port, uint8_t state);

#endif // GPIO_DRIVER_H
