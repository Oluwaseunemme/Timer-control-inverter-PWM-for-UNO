#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

uint16_t TOP_VALUE;
volatile uint16_t pwmValue;

uint16_t getResolution(uint8_t resolution)//this switch case helps convert input resolution in bit like 8, 9 and 10 into it's max unit 
{
    switch (resolution)
    {
        case 8:
            return 255;

        case 9:
            return 511;

        case 10:
            return 1023;

        default:
            return 0;
    }
}


uint16_t setPwm(uint16_t freq,
                uint8_t resolution,
                uint16_t duty){//
    const uint16_t prescaler = 8;//prescaler of 8 basically helps scale down our clock by a factor of 8 

    uint16_t maxDuty = getResolution(resolution);

    if (maxDuty == 0) return 0;

    // Mode 8:
    // fPWM = F_CPU / (2 × prescaler × TOP)
    uint32_t top = F_CPU / (2UL * prescaler * freq);

    if (top > 65535) return 0;

    TOP_VALUE = (uint16_t)top;

    // Convert duty command to timer compare value
    uint16_t compare= (uint16_t)(((uint32_t)duty * TOP_VALUE) / maxDuty);
    //uint16_t pin10Value=  TOP_VALUE-pin9Value;
    //uint16_t compare[2] = [pin9Value, pin10Value];

    return compare;
}


void setup()
{
    // Arduino pins 9 and 10
    DDRB |= _BV(PB1) | _BV(PB2);

    // Timer TOP
    TOP_VALUE =
        F_CPU / (2UL * 8UL * 50UL);

    ICR1 = TOP_VALUE;

    // Mode 8
    // COM1A1:0 = 10
    // COM1B1:0 = 10
    // WGM11 = 0
    TCCR1A =
    _BV(COM1A1) |              // OC1A non-inverting
    _BV(COM1B1) | _BV(COM1B0); // OC1B inverting

    // WGM13 = 1
    // WGM12 = 0
    // CS11 = 1 → prescaler /8
    TCCR1B =
        _BV(WGM13) |
        _BV(CS11);

    // Enable Timer1 overflow interrupt
    TIMSK1 =
        _BV(TOIE1);

    sei();
}


void loop()
{

}


ISR(TIMER1_OVF_vect)
{   
    uint16_t pin9Val= setPwm(50, 8, 50);
    OCR1A = pin9Val+1000;
    OCR1B = pin9Val;
}