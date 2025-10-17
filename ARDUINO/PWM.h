
#ifndef PWM_H
#define PWM_H

// High-resolution PWM on Arduino Mega using Timer3 (for pin 2)
// Define the PWM parameters
#define PWM_PIN 2          // Pin 2 (OC3B) connected to the motor
#define PWM_FREQUENCY 600000// Frequency in Hz (e.g., 2 kHz)
#define DUTY_CYCLE 50      // Duty cycle in percentage (e.g., 50%)
///////////////////////////////
class PWM
{
  public:
      PWM();
      void init(char pin, int frequency);
      void start(int duty_cycle);
      void stop(void);
      void updateDutyCycle(int dutyCycle);
      void enable(void);
      void disable(void);
  private:
      void setupTimer3(int frequency, int dutyCycle);

};
/////////////////////////////////
#endif
