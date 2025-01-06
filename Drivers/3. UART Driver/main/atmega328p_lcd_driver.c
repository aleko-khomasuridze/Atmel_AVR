#include "atmega328p_lcd_driver.h"


/* Function to send a command to the LCD */
void LCD_SendCommand(LCD_GpioPins *lcdPins, uint8_t command) {
    // Ensure the RS (Register Select) is low for command mode
    GPIO_WritePin(lcdPins->RS->GPIOx, lcdPins->RS->pinNumber, GPIO_PIN_RESET);
    // Ensure the RW (Read/Write) is low for write mode
    GPIO_WritePin(lcdPins->RW->GPIOx, lcdPins->RW->pinNumber, GPIO_PIN_RESET);
    
    // Write each bit of the command to the corresponding data pins
    for (uint8_t i = 0; i < 8; i++) {
        GPIO_WritePin(lcdPins->D[i].GPIOx, lcdPins->D[i].pinNumber, (command >> i) & 1U);
    }
    
    // Pulse the EN (Enable) pin to process the command
    GPIO_WritePin(lcdPins->EN->GPIOx, lcdPins->EN->pinNumber, GPIO_PIN_SET);
    _delay_ms(1); // Ensure the enable pulse width is long enough
    GPIO_WritePin(lcdPins->EN->GPIOx, lcdPins->EN->pinNumber, GPIO_PIN_RESET);
}

/* Function to write a single character to the LCD */
void LCD_WriteChar(LCD_GpioPins *lcdPins, char data) {
    // Set RS high for data mode
    GPIO_WritePin(lcdPins->RS->GPIOx, lcdPins->RS->pinNumber, GPIO_PIN_SET);
    // Ensure RW is low for write mode
    GPIO_WritePin(lcdPins->RW->GPIOx, lcdPins->RW->pinNumber, GPIO_PIN_RESET);
    
    // Write each bit of the data to the corresponding data pins
    for (uint8_t i = 0; i < 8; i++) {
        GPIO_WritePin(lcdPins->D[i].GPIOx, lcdPins->D[i].pinNumber, (data >> i) & 1U);
    }
    
    // Pulse the EN pin to process the data
    GPIO_WritePin(lcdPins->EN->GPIOx, lcdPins->EN->pinNumber, GPIO_PIN_SET);
    _delay_ms(1); // Ensure the enable pulse width is long enough
    GPIO_WritePin(lcdPins->EN->GPIOx, lcdPins->EN->pinNumber, GPIO_PIN_RESET);
    _delay_ms(1); // Short delay to ensure the character is processed
}

void LCD_WriteString(LCD_GpioPins *lcdPins, char* msg) {
	while (*msg) {
		LCD_WriteChar(lcdPins, *msg++);
	}
}


void LCD_GpioInit(LCD_GpioPins *lcdPins) {
	
	GPIO_InitTypeDef lcdGpio = {
		.Mode = GPIO_MODE_OUTPUT,
		.Pull = GPIO_NOPULL,
		.Speed = GPIO_SPEED_FAST
	};
	
	lcdGpio.Pin = lcdPins->RS->pinNumber;
	GPIO_Init(lcdPins->RS->GPIOx, &lcdGpio);
	
	lcdGpio.Pin = lcdPins->EN->pinNumber;
	GPIO_Init(lcdPins->EN->GPIOx, &lcdGpio);
	
	lcdGpio.Pin = lcdPins->RW->pinNumber;
	GPIO_Init(lcdPins->RW->GPIOx, &lcdGpio);
	
	for (uint8_t index = 0; index < 8; index++) {
		lcdGpio.Pin = lcdPins->D[index].pinNumber;
		GPIO_Init(lcdPins->D[index].GPIOx, &lcdGpio);
	}
	
}

void LCD_Init(LCD_ConfigTypeDef *LCD_Config) {
	LCD_GpioInit(LCD_Config->pins);
	
	_delay_ms(30);
	
	LCD_SendCommand(LCD_Config->pins, LCD_STARTUP);
	LCD_SendCommand(LCD_Config->pins, LCD_MOVE_CURSOR_RIGHT);
	LCD_SendCommand(LCD_Config->pins, LCD_CLEAR_SCREEN);
	LCD_SendCommand(LCD_Config->pins, LCD_TURN_ON_BLINK_CURSOR);
	
}

void LCD_Clear(LCD_GpioPins *lcdPins) {
    LCD_SendCommand(lcdPins, LCD_CLEAR_SCREEN);
    _delay_ms(2); // Clear command takes longer to complete
}
