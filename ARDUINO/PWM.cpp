#include "Arduino.h"
#include "PWM.h"
//__________________________________________________________________________________________________________________________________________________________________
PWM::PWM()  // // Constructor
{
}
//__________________________________________________________________________________________________________________________________________________________________
/**
* @brief initialize the pwm module
* @param pin pwm output pin
* @param frequency generated pwm frequency
* @param dutyCycle initial duty cycle, later can be changed using updateDutyCycle function
* @return void
*/
void PWM::init(char pin, int frequency)
{
  pinMode(PWM_PIN, OUTPUT);   // Set PWM pin as output
  digitalWrite(PWM_PIN,LOW);  // set initial low state, else motor will trigger in full power
  setupTimer3(PWM_FREQUENCY, DUTY_CYCLE); // setup timer
  updateDutyCycle(0);                     // no generate pwm, idle
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief generate PWM with low duty cycle
 * @param dutyCycle to set the duty cycle of pwm 1-100
 * @return void
 */
void PWM::start(int dutyCycle) 
{
   updateDutyCycle(dutyCycle);
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief stop PWM generation
 * @param void
 * @return void
 */
void PWM::stop(void) 
{
   updateDutyCycle(0);
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief update duty cycle dynamically
 * @param dutyCycle to set the duty cycle of pwm 1-100
 * @return void
 */
void PWM::updateDutyCycle(int dutyCycle) 
{
  int timerCounts = ICR3;
  int dutyCounts = (timerCounts * dutyCycle) / 100;
  OCR3B = dutyCounts; // Update the duty cycle
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Function to set up Timer3 for high-resolution PWM
 * @param frequency set PWM frequency 
 * @param dutyCycle set duty cycle
 * @return void
 */
void PWM::setupTimer3(int frequency, int dutyCycle) {
  // Stop Timer3
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3 = 0;

  // Calculate the timer counts for the given frequency
  int timerCounts = (16000000 / (frequency * 2)) - 1; // 16 MHz clock, Prescaler = 1

  // Set the duty cycle
  int dutyCounts = (timerCounts * dutyCycle) / 100;

  // Configure Timer3 for PWM
  TCCR3A = (1 << COM3B1) | (1 << WGM31); // Non-inverting PWM on OC3B, Fast PWM mode
  TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS30); // Fast PWM, Prescaler = 1

  ICR3 = timerCounts; // Set the TOP value
  OCR3B = dutyCounts; // Set the duty cycle
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Enable PWM output by starting the timer
 * @return void
 */
void PWM::enable() 
{
  TCCR3B |= (1 << CS30); // Set the prescaler to start the timer
}

//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Disable PWM output by stopping the timer
 * @return void
 */
void PWM::disable() 
{
  TCCR3B &= ~(1 << CS30); // Clear the prescaler bits to stop the timer
}
