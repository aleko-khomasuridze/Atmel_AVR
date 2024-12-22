#ifndef __ATMEGA328P_LCD_DRIVER_H__
#define __ATMEGA328P_LCD_DRIVER_H__


#include "atmega328p_gpio_driver.h"
#include <util/delay.h>


/*
 * @breif LCD commands
 */
#define LCD_STARTUP						0x30U
#define LCD_CLEAR_SCREEN				0x01U
#define LCD_MOVE_CURSOR_RIGHT			0x06U
#define LCD_TURN_ON_BLINK_CURSOR		0x0FU

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    LCD_DATA_MODE_8BIT,
    LCD_DATA_MODE_4BIT
} LCD_DataMode;

typedef struct {
	uint8_t *GPIOx;
	uint8_t pinNumber;
} LCD_GpioPinTypeDef;

typedef struct {
	LCD_GpioPinTypeDef *EN;
	LCD_GpioPinTypeDef *RS;
	LCD_GpioPinTypeDef *RW;
	LCD_GpioPinTypeDef *D;
} LCD_GpioPins;

typedef struct {
	LCD_GpioPins *pins;
	LCD_DataMode mode;
} LCD_ConfigTypeDef;

#ifdef __cplusplus
}
#endif

#endif //__ATMEGA328P_GPIO_DRIVER_H__