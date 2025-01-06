#ifndef __ATMEGA328P_GPIO_DRIVER_H__
#define __ATMEGA328P_GPIO_DRIVER_H__

#include <avr/io.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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
void GPIO_Init(GPIOPin pin, GPIODirection direction);
GPIOState GPIO_ReadPin(GPIOPin pin);
void GPIO_WritePin(GPIOPin pin, GPIOState state);
void GPIO_Toggle(GPIOPin pin);
void GPIO_WritePort(volatile uint8_t *port, uint8_t state);

#ifdef __cplusplus
}
#endif

#endif // __ATMEGA328P_GPIO_DRIVER_H__
