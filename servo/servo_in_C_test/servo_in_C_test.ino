/**********************************************************************
 * Title: AVR Microcontroller PWM servo control Example
 * Description:
 * This program demonstrates PWM (Pulse Width Modulation) control on
 * an AVR microcontroller, specifically configuring and using Timer 1
 * in Fast PWM mode to smoothly turn a servo motor connected to pin 9.
 * The Servo angle is gradually increased and then decreased in a
 * repeating pattern.
 *
 * Components:
 * - AVR microcontroller (e.g., Arduino board) 
 * - Servo connected to pin 9
 *
 * Configuration:
 * - Timer 1 is configured for Fast PWM mode with a prescaler of 8,
 *   resulting in a PWM frequency suitable for Servo control.
 * - The PWM duty cycle is adjusted by changing the value of OCR1A.
 *
 * Author: Aleko Khomasuridze
 * Date: September 25, 2023
 **********************************************************************/


#define SERVO_SIGNAL_MAX 4500
#define SERVO_SIGNAL_MIN 1300


int main(void) {
  // Configure Timer 1 for Fast PWM mode
  DDRB |= (1 << DDB1);

  // Clear the Timer/Counter1 Control Register A (TCCR1A)
  TCCR1A = 0;

  // Configure TCCR1A with specific settings:
  // - Set COM1A1 and COM1B1 to configure OC1A and OC1B pins in non-inverted (clear on compare match) output mode.
  // - Set WGM11 to configure the waveform generation mode.
  TCCR1A = (1 << COM1A1) | (1 << WGM11);

  // Clear the Timer/Counter1 Control Register B (TCCR1B)
  TCCR1B = 0;

  // Configure TCCR1B with specific settings:
  // - Set WGM13, WGM12, and CS11.
  //   - WGM13 and WGM12 are used to configure the waveform generation mode (specific mode depends on other settings).
  //   - CS11 is used to set a prescaler of 8, which divides the clock frequency by 8.
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);


  ICR1 = 40000;  // Set the top value for the timer (controls PWM frequency)
  OCR1A = SERVO_SIGNAL_MIN;  // Initialize the PWM value for pin 9 (controls duty cycle)


  while (true) {

    // Increase the value of OCR1A from 1300 to 4400 in steps of 100
    for (uint16_t i = SERVO_SIGNAL_MIN; i < SERVO_SIGNAL_MAX; i += 25) {

      OCR1A = i;      // Set the Output Compare Register A (OCR1A) to the current value of i
      _delay_ms(15);  // Wait for 20 milliseconds
    }

    //_delay_ms(200);  // Wait for 200 milliseconds

    // Decrease the value of OCR1A from 4400 to 1300 in steps of 100
    for (uint16_t i = SERVO_SIGNAL_MAX; i > SERVO_SIGNAL_MIN; i -= 25) {

      OCR1A = i;      // Set the Output Compare Register A (OCR1A) to the current value of i
      _delay_ms(15);  // Wait for 20 milliseconds
    }

    //_delay_ms(200);   // Wait for 200 milliseconds
  }
  
}