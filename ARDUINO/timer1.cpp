#include "Arduino.h"
#include "timer1.h"

// Define a global instance of Timer1
timer1 t1;

//__________________________________________________________________________________________________________________________________________________________________
/**
* @brief Timer1 interrupt service routine
* @return void
*/
//__________________________________________________________________________________________________________________________________________________________________
ISR(TIMER1_COMPA_vect) 
{
    digitalWrite(23, !digitalRead(23)); // Toggle LED
    if (!t1.completed) 
    {
        t1.countReg++; 
        if (t1.countReg >= t1.targetVal) 
        {
            t1.completed = true;            
        }
    }
}

//__________________________________________________________________________________________________________________________________________________________________
/**
* @brief Timer1 Constructor
*/
//__________________________________________________________________________________________________________________________________________________________________
timer1::timer1()  
{
    countReg = 0;
    targetVal = 0;
    completed = true;
}

//__________________________________________________________________________________________________________________________________________________________________
/**
* @brief Initialize the Timer1 module
* @param milliseconds Timer interval in milliseconds
* @return void
*/
//__________________________________________________________________________________________________________________________________________________________________
void timer1::init(long milliseconds)
{
    cli(); // Disable global interrupts

    TCCR1A = 0; // Clear Timer/Counter Control Register A
    TCCR1B = 0; // Clear Timer/Counter Control Register B
    TCNT1 = 0;  // Initialize counter value to 0

    // Set compare match register for the given delay
    OCR1A = getValFromMilliseconds(milliseconds);

    // Set Timer1 in CTC mode (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    // Set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // Enable Timer1 compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    sei(); // Enable global interrupts
}

//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Convert milliseconds to Timer1 config register value
 * @param milliseconds Timer interval in milliseconds
 * @return Timer1 register value
 */
//__________________________________________________________________________________________________________________________________________________________________
long timer1::getValFromMilliseconds(long milliseconds)
{
    // Calculate the Timer Compare Value
    long compareValue = (milliseconds * (16000000 / 1024)) / 1000;

    // Limit the compare value to the timer range (16-bit for Timer1)
    return (compareValue > 65535) ? 65535 : compareValue;
}

//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Enable Timer1 module
 * @return void
 */
//__________________________________________________________________________________________________________________________________________________________________
void timer1::enable() 
{
    TIMSK1 |= (1 << OCIE1A); // Enable timer compare interrupt
}

//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Disable Timer1 module
 * @return void
 */
//__________________________________________________________________________________________________________________________________________________________________
void timer1::disable() 
{
    TIMSK1 &= ~(1 << OCIE1A); // Disable timer compare interrupt
}

//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Set Tick interval
 * @param milliseconds Timer interval in milliseconds
 * @return void
 */
//__________________________________________________________________________________________________________________________________________________________________
void timer1::target_count(long milliseconds)
{
    targetVal = milliseconds;
    countReg = 0;
    completed = false;
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Start the count for a specified interval
 * @param stop timer1 count
 * @return void
 */
void timer1::reset()
{
    countReg = 0;
    completed = false;
}
//__________________________________________________________________________________________________________________________________________________________________

