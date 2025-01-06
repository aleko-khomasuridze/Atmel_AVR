#include "atmega328p_lcd_driver.h"

int main(void) {
  // Define the GPIO pins for the LCD
  LCD_GpioPinTypeDef RS = {GPIOB, PIN0};
  LCD_GpioPinTypeDef RW = {GPIOB, PIN1};
  LCD_GpioPinTypeDef EN = {GPIOB, PIN2};
  LCD_GpioPinTypeDef D[8] = {
    {GPIOC, PIN0},
    {GPIOC, PIN1},
    {GPIOC, PIN2},
    {GPIOC, PIN3},
    {GPIOC, PIN4},
    {GPIOC, PIN5},
    {GPIOC, PIN6},
    {GPIOC, PIN7}
  };

  // Define LCD GPIO pins
  LCD_GpioPins lcdPins = {
    .EN = &EN,
    .RS = &RS,
    .RW = &RW,
    .D = D
  };

  // Define LCD configuration
  LCD_ConfigTypeDef lcdConfig = {
    .pins = &lcdPins,
    .mode = LCD_DATA_MODE_8BIT
  };

  LCD_Init(&lcdConfig);

  LCD_WriteString(lcdConfig.pins, "Hello, World!");
  _delay_ms(5000);
  LCD_Clear(lcdConfig.pins);
  LCD_WriteString(lcdConfig.pins, "LCD Test Passed!");

  while (1) {
    // Infinite loop
  }

  return 0;
}
