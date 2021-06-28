#include "TriggerPattern.h"
#include "Protocol.h"
#include "Communicator.h"

TriggerPattern* TriggerPattern::triggerPattern = nullptr;
volatile TriggerPattern::ROTATION_DIRECTION TriggerPattern::rotation_direction = TriggerPattern::ROTATION_DIRECTION::CLOCKWISE;

TriggerPattern::TriggerPattern(Packet *rx, Packet *tx)
{
    this->rx = rx;
    this->tx = tx;
    triggerPattern = this;
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

void TriggerPattern::processCommands()
{
    if (nullptr == tx || nullptr == rx || !rx->pending() || !(Command::TRIGGER_PATTERN_CMD_MASK == rx->commandType()))
    {
        return;
    }

    switch (rx->command())
    {
    case Command::TRIGGER_PATTERN_INDEX:
        processCommandIndex();
        break;
    case Command::TRIGGER_PATTERN_NAME:
        processCommandName();
        break;
    case Command::TRIGGER_PATTERN_DATA:
        processCommandData();
        break;
    case Command::TRIGGER_PATTERN_DEGREES:
        processCommandDegrees();
        break;
    case Command::TRIGGER_PATTERN_ROTATION:
        processCommandRotation();
        break;
    case Command::TRIGGER_PATTERN_RPM:
        processCommandRpm();
        break;
    case Command::TRIGGER_PATTERN_COUNT:
        processCommandCount();
        break;
    case Command::TRIGGER_PATTERN_ENABLE:
        processCommandEnable();
        break;
    default:
        break;
    }

    rx->reset();
}

void TriggerPattern::processCommandIndex()
{
    if (rx->hardwareIndex() < PATTERNS_COUNT)
    {
        if (Operation::WRITE == rx->operation())
        {
            pattern_index = rx->hardwareIndex();
        }
    }

    tx->setHardwareIndex(pattern_index);
    tx->setCommand(rx->command());
    tx->setOperation(rx->operation());
}

void TriggerPattern::processCommandName()
{
    if (rx->hardwareIndex() < PATTERNS_COUNT)
    {
        if (Operation::READ == rx->operation())
        {
            const char *p = _patterns[rx->hardwareIndex()].decoder_name;
            uint8_t byte = 0;
            
            while ((byte = pgm_read_byte(p++)))
            {
                if (!tx->appendData(&byte, 1))
                {
                    break;
                }
            }
            
            tx->setHardwareIndex(rx->hardwareIndex());
            tx->setCommand(rx->command());
            tx->setOperation(rx->operation());
        }
    }
}

void TriggerPattern::processCommandData()
{
    if (rx->hardwareIndex() < PATTERNS_COUNT)
    {
        if (Operation::READ == rx->operation())
        {
            const unsigned char *p = _patterns[rx->hardwareIndex()].edge_states_ptr;
            
            if (tx->appendData(p, _patterns[rx->hardwareIndex()].wheel_max_edges, true))
            {
                tx->setHardwareIndex(rx->hardwareIndex());
                tx->setCommand(rx->command());
                tx->setOperation(rx->operation());
            }
        }
    }
}

void TriggerPattern::processCommandDegrees()
{
    if (rx->hardwareIndex() < PATTERNS_COUNT)
    {
        if (Operation::READ == rx->operation())
        {
            if (tx->appendData(&_patterns[rx->hardwareIndex()].wheel_degrees, sizeof(uint16_t), true))
            {
                tx->setHardwareIndex(rx->hardwareIndex());
                tx->setCommand(rx->command());
                tx->setOperation(rx->operation());
            }
        }
    }
}
void TriggerPattern::processCommandRotation()
{
    if (rx->hardwareIndex() == pattern_index)
    {
        uint8_t value = 0;

        if (Operation::WRITE == rx->operation())
        {
            if (rx->getDataBytesCount() > 0)
            {
                uint8_t value = rx->getDataPointer()[0];
                if (ROTATION_DIRECTION::CLOCKWISE == value 
                || ROTATION_DIRECTION::COUNTERCLOCKWISE == value)
                {
                    rotation_direction = (ROTATION_DIRECTION)(value);
                }
            }
        }
        
        value = (uint8_t)rotation_direction;
        if (tx->appendData(&value, 1))
        {
            tx->setHardwareIndex(rx->hardwareIndex());
            tx->setCommand(rx->command());
            tx->setOperation(rx->operation());
        }
    }
}

void TriggerPattern::processCommandRpm()
{
    if (rx->hardwareIndex() == pattern_index)
    {
        if (Operation::WRITE == rx->operation())
        {
            if (rx->getDataBytesCount() > 1)
            {
                uint16_t value =  (uint16_t)(rx->getDataPointer()[0] << 8) & rx->getDataPointer()[1];

                if (value < min_rpm)
                {
                    value = min_rpm;
                }
                else if (value > max_rpm)
                {
                    value = max_rpm;
                }
                
                rpm = value;
            }
        }
        
        if (tx->appendData(&rpm, 2))
        {
            tx->setHardwareIndex(rx->hardwareIndex());
            tx->setCommand(rx->command());
            tx->setOperation(rx->operation());
        }
    }
}

void TriggerPattern::processCommandCount()
{
    uint8_t value = PATTERNS_COUNT;

    if (tx->appendData(&value, 1))
    {
        tx->setHardwareIndex(pattern_index);
        tx->setCommand(rx->command());
        tx->setOperation(rx->operation());
    }
}

void TriggerPattern::processCommandEnable()
{
    if (rx->hardwareIndex() == pattern_index)
    {
        if (Operation::WRITE == rx->operation())
        {
            if (rx->getDataBytesCount() > 0)
            {
                enabled = (bool)(rx->getDataPointer()[0]);
            }
        }

        if (tx->appendData(&enabled, 1))
        {
            tx->setHardwareIndex(pattern_index);
            tx->setCommand(rx->command());
            tx->setOperation(rx->operation());
        }
    }
}

volatile uint8_t TriggerPattern::pattern_index = 0;
uint16_t TriggerPattern::rpm = 1200;
volatile uint8_t TriggerPattern::prescaler_bits = 0;
volatile uint8_t TriggerPattern::last_prescaler_bits = 0;
volatile uint16_t TriggerPattern::new_OCR1A = 5000; /* sane default */
volatile bool TriggerPattern::reset_prescaler = false;
uint16_t TriggerPattern::wanted_rpm = 6000;

void TriggerPattern::reset_new_OCR1A(uint32_t new_rpm)
{
    /*  */
    uint32_t tmp;
    uint8_t bitshift;
    uint8_t tmp_prescaler_bits;

    tmp = (uint32_t)(8000000.0 / (Wheels[pattern_index].rpm_scaler * (float)(new_rpm < 10 ? 10 : new_rpm)));

    triggerPattern->get_prescaler_bits(&tmp, &tmp_prescaler_bits, &bitshift);

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
    static uint16_t edge_counter = 0;
    // Not used
    static volatile uint8_t output_invert_mask = 0x00;

    // Write trigger data at _current_index to port
    PORTB = output_invert_mask ^ pgm_read_byte(&Wheels[pattern_index].edge_states_ptr[edge_counter]);

    // Overflow handling of edge_counter index, based on the direction of rotation
    if (ROTATION_DIRECTION::CLOCKWISE == rotation_direction)
    {
        edge_counter++;
        if (edge_counter == Wheels[pattern_index].wheel_max_edges)
        {
            edge_counter = 0;
        }
    }
    else
    {
        if (edge_counter == 0)
        {
            edge_counter = Wheels[pattern_index].wheel_max_edges;
        }
        edge_counter--;
    }

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