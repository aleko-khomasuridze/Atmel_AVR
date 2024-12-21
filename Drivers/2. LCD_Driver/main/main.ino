#include "atmega328p_gpio_driver.h"
#include <util/delay.h>  // for _delay_ms function

int main(void) {
    GPIOPin ledPin = {&DDRB, &PORTB, &PINB, PB5};  // Pin 13 on Arduino
  
    GPIO_init(ledPin, GPIO_DIR_OUTPUT);

    while (1) {
        GPIO_write(ledPin, GPIO_HIGH);
        _delay_ms(2000);  // Keep LED on for a while
        GPIO_write(ledPin, GPIO_LOW);
        _delay_ms(2000);  // Keep LED off for a while
    }
}