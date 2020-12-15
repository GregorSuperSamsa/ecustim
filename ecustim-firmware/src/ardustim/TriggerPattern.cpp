#include "TriggerPattern.h"

volatile TriggerPattern::ROTATION TriggerPattern::_rotation = TriggerPattern::ROTATION::CLOCKWISE;
TriggerPattern triggerPattern;
TriggerPattern::TriggerPattern()
{
    triggerPattern = *this;
}

void TriggerPattern::setCurrent(const uint8_t &index)
{
    if ((_current_index != index) && ((index <= PATTERNS_COUNT)))
    {
        _current_index = index;
    }
}

uint8_t TriggerPattern::current() const
{
    return _current_index;
}

void TriggerPattern::setRpm(const uint32_t &rpm)
{
    if (_rpm != rpm)
    {
        _rpm = rpm;
    }
}

uint32_t TriggerPattern::rpm() const
{
    return _rpm;
}

const char *TriggerPattern::name() const
{
    return _patterns[_current_index].decoder_name;
}

void TriggerPattern::begin()
{
    // Stop all interrupts
    cli();

    /* Configuring TIMER1 (pattern generator) */
    // Set timer1 to generate pulses
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    // Set compare register to sane default
    OCR1A = 1000; /* 8000 RPM (60-2) */

    // Turn on CTC mode
    TCCR1B |= (1 << WGM12); // Normal mode (not PWM)
    // Set prescaler to 1
    TCCR1B |= (1 << CS10); /* Prescaler of 1 */
    // Enable output compare interrupt for timer channel 1 (16 bit)
    TIMSK1 |= (1 << OCIE1A);

    // // Set timer2 to run sweeper routine
    // TCCR2A = 0;
    // TCCR2B = 0;
    // TCNT2 = 0;

    // // Set compare register to sane default
    // OCR2A = 249;  /* With prescale of x64 gives 1ms tick */

    // // Turn on CTC mode
    // TCCR2A |= (1 << WGM21); // Normal mode (not PWM)
    // // Set prescaler to x64
    // TCCR2B |= (1 << CS22); /* Prescaler of 64 */
    // // Enable output compare interrupt for timer channel 2
    // TIMSK2 |= (1 << OCIE2A);

    /* Configure ADC as per http://www.glennsweeney.com/tutorials/interrupt-driven-analog-conversion-with-an-atmega328p */
    // clear ADLAR in ADMUX (0x7C) to right-adjust the result
    // ADCL will contain lower 8 bits, ADCH upper 2 (in last two bits)
    ADMUX &= B11011111;

    // Set REFS1..0 in ADMUX (0x7C) to change reference voltage to the
    // proper source (01)
    ADMUX |= B01000000;

    // Clear MUX3..0 in ADMUX (0x7C) in preparation for setting the analog
    // input
    ADMUX &= B11110000;

    // Set MUX3..0 in ADMUX (0x7C) to read from AD8 (Internal temp)
    // Do not set above 15! You will overrun other parts of ADMUX. A full
    // list of possible inputs is available in Table 24-4 of the ATMega328
    // datasheet
    // ADMUX |= 8;
    // ADMUX |= B00001000; // Binary equivalent

    // Set ADEN in ADCSRA (0x7A) to enable the ADC.
    // Note, this instruction takes 12 ADC clocks to execute
    ADCSRA |= B10000000;

    // Set ADATE in ADCSRA (0x7A) to enable auto-triggering.
    ADCSRA |= B00100000;

    // Clear ADTS2..0 in ADCSRB (0x7B) to set trigger mode to free running.
    // This means that as soon as an ADC has finished, the next will be
    // immediately started.
    ADCSRB &= B11111000;

    // Set the Prescaler to 128 (16000KHz/128 = 125KHz)
    // Above 200KHz 10-bit results are not reliable.
    ADCSRA |= B00000111;

    // Set ADIE in ADCSRA (0x7A) to enable the ADC interrupt.
    // Without this, the internal interrupt will not trigger.
    ADCSRA |= B00001000;

    pinMode(8, OUTPUT);  /* Primary (crank usually) output */
    pinMode(9, OUTPUT);  /* Secondary (cam usually) output */
    pinMode(10, OUTPUT); /* Knock signal for seank, ony on LS1 pattern, NOT IMPL YET */

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    pinMode(53, OUTPUT);
    pinMode(52, OUTPUT);
#endif

    sei(); // Enable interrupts
    // Set ADSC in ADCSRA (0x7A) to start the ADC conversion
    ADCSRA |= B01000000;
    /* Make sure we are using the DEFAULT RPM on startup */
    reset_new_OCR1A(wanted_rpm);
}

void TriggerPattern::setRotation(const TriggerPattern::ROTATION &rotation)
{
    if (_rotation != rotation)
    {
        _rotation = rotation;
    }
}

TriggerPattern::ROTATION TriggerPattern::rotation() const
{
    return _rotation;
}

volatile uint8_t TriggerPattern::_current_index = 0;
uint32_t TriggerPattern::_rpm = 1200;
volatile uint8_t TriggerPattern::output_invert_mask = 0x00;
volatile uint8_t TriggerPattern::prescaler_bits = 0;
volatile uint8_t TriggerPattern::last_prescaler_bits = 0;
volatile uint8_t TriggerPattern::mode = 0;
volatile uint16_t TriggerPattern::new_OCR1A = 5000; /* sane default */
volatile bool TriggerPattern::reset_prescaler = false;
uint16_t TriggerPattern::wanted_rpm = 6000;

void TriggerPattern::reset_new_OCR1A(uint32_t new_rpm)
{
    
    uint32_t tmp;
    uint8_t bitshift;
    uint8_t tmp_prescaler_bits;
    tmp = (uint32_t)(8000000.0 / (Wheels[_current_index].rpm_scaler * (float)(new_rpm < 10 ? 10 : new_rpm)));

    triggerPattern.get_prescaler_bits(&tmp, &tmp_prescaler_bits, &bitshift);

    new_OCR1A = (uint16_t)(tmp >> bitshift);
    prescaler_bits = tmp_prescaler_bits;
    reset_prescaler = true;
}

enum
{
    PRESCALE_1 = 1,
    PRESCALE_8 = 2,
    PRESCALE_64 = 3,
    PRESCALE_256 = 4,
    PRESCALE_1024 = 5,
    RECALC
};

uint8_t TriggerPattern::get_bitshift_from_prescaler(uint8_t *prescaler_bits)
{
    switch (*prescaler_bits)
    {
    case PRESCALE_1024:
        return 10;
    case PRESCALE_256:
        return 8;
    case PRESCALE_64:
        return 6;
    case PRESCALE_8:
        return 3;
    case PRESCALE_1:
        return 0;
    }
    return 0;
}



// Gets prescaler enum and bitshift based on OC value
void TriggerPattern::get_prescaler_bits(uint32_t *potential_oc_value, uint8_t *prescaler, uint8_t *bitshift)
{
    if (*potential_oc_value >= 16777216)
    {
        *prescaler = PRESCALE_1024;
        *bitshift = 10;
    }
    else if (*potential_oc_value >= 4194304)
    {
        *prescaler = PRESCALE_256;
        *bitshift = 8;
    }
    else if (*potential_oc_value >= 524288)
    {
        *prescaler = PRESCALE_64;
        *bitshift = 6;
    }
    else if (*potential_oc_value >= 65536)
    {
        *prescaler = PRESCALE_8;
        *bitshift = 3;
    }
    else
    {
        *prescaler = PRESCALE_1;
        *bitshift = 0;
    }
}


/* Pumps the pattern out of flash to the port 
 * The rate at which this runs is dependent on what OCR1A is set to
 * the sweeper in timer2 alters this on the fly to alow changing of RPM
 * in a very nice way
 */

void TriggerPattern::timer1Handler()
{
    static volatile uint16_t edge_counter = 0;
   
Serial.println(edge_counter);

    /* This is VERY simple, just walk the array and wrap when we hit the limit */
    PORTB = output_invert_mask ^ pgm_read_byte(&Wheels[_current_index].edge_states_ptr[edge_counter]); /* Write it to the port */
    /* Normal direction  overflow handling */
    if (ROTATION::CLOCKWISE == TriggerPattern::_rotation)
    {
        edge_counter++;
        if (edge_counter == Wheels[_current_index].wheel_max_edges)
        {
            edge_counter = 0;
        }
    }
    else
    {
        if (edge_counter == 0) 
        {
            edge_counter = Wheels[_current_index].wheel_max_edges;
        }
        edge_counter--;
    }
    /* The tables are in flash so we need pgm_read_byte() */

    /* Reset Prescaler only if flag is set */
    if (reset_prescaler)
    {
        // Clear CS10, CS11 and CS12
        TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
        TCCR1B |= prescaler_bits;
        reset_prescaler = false;
    }

    // Reset next compare value for RPM changes
    // Apply new "RPM" from Timer2 ISR, i.e. speed up/down the virtual "wheel"
    OCR1A = new_OCR1A;

}

ISR(TIMER1_COMPA_vect)
{
    TriggerPattern::timer1Handler();
}