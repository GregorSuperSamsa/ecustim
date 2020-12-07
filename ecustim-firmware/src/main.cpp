/*
 * Arbritrary wheel pattern generator
 *
 * copyright 2014 David J. Andruczyk
 * 
 * Ardu-Stim software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ArduStim software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any ArduStim software.  If not, see http://www.gnu.org/licenses/
 *
 */

#include <Arduino.h>
#include "ardustim/defines.h"
#include "ardustim/ardustim.h"
#include "ardustim/enums.h"
#include "ardustim/comms.h"
#include "ardustim/storage.h"
#include "ardustim/user_defaults.h"
#include "ardustim/TriggerPattern.h"


uint16_t wanted_rpm = 6000;                                                     

// Sensistive stuff used in ISR's
volatile uint8_t fraction = 0;
volatile uint16_t adc0; /* POT RPM */
volatile uint16_t adc1; /* Pot Wheel select */
volatile uint32_t oc_remainder = 0;

// Setting rpm to any value over 0 will enabled sweeping by default
// Stuff for handling prescaler changes (small tooth wheels are low RPM)
volatile uint8_t analog_port = 0;
volatile bool adc0_read_complete = false;
volatile bool adc1_read_complete = false;
volatile bool reset_prescaler = false;
volatile bool normal = true;

// Don't invert anything
volatile uint8_t output_invert_mask = 0x00; 

volatile uint8_t prescaler_bits = 0;
volatile uint8_t last_prescaler_bits = 0;
volatile uint8_t mode = 0;
volatile uint16_t new_OCR1A = 5000; /* sane default */
volatile uint16_t edge_counter = 0;

// Less sensitive globals
uint8_t bitshift = 0;




void setup_hardware()
{
  cli(); // stop interrupts

  /* Configuring TIMER1 (pattern generator) */
  // Set timer1 to generate pulses
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Set compare register to sane default
  OCR1A = 1000;  /* 8000 RPM (60-2) */

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


  pinMode(8, OUTPUT); /* Primary (crank usually) output */
  pinMode(9, OUTPUT); /* Secondary (cam usually) output */
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

void setup() 
{
  setup_serial();

  loadConfig();

  setup_hardware();
}




//! ADC ISR for alternating between ADC pins 0 and 1
/*!
 * Reads ADC ports 0 and 1 alternately. Port 0 is RPM, Port 1 is for
 * future fun (possible wheel selection)
 */
ISR(ADC_vect)
{
  if (analog_port == 0)
  {
    adc0 = ADCL | (ADCH << 8);
	  adc0_read_complete = true;
    /* Flip to channel 1 */
    //ADMUX |= B00000001;
    //analog_port = 1;
    /* Trigger another conversion */
    //ADCSRA |= B01000000;
    return;
  } 
//  if (analog_port == 1)
//  {
//    adc1 = ADCL | (ADCH << 8);
//	adc1_read_complete = true;
//    /* Flip to channel 0 */
//    /* Tell it to read ADC0, clear MUX0..3 */
//    ADMUX &= B11110000;
//    analog_port = 0;
//    /* Trigger another conversion */
//    ADCSRA |= B01000000;
//    return;
//  }
}

/* Pumps the pattern out of flash to the port 
 * The rate at which this runs is dependent on what OCR1A is set to
 * the sweeper in timer2 alters this on the fly to alow changing of RPM
 * in a very nice way
 */
ISR(TIMER1_COMPA_vect) 
{
  /* This is VERY simple, just walk the array and wrap when we hit the limit */
  PORTB = output_invert_mask ^ pgm_read_byte(&triggerPattern.Wheels[selected_wheel].edge_states_ptr[edge_counter]);   /* Write it to the port */
  /* Normal direction  overflow handling */
  if (normal)
  {
    edge_counter++;
    if (edge_counter == triggerPattern.Wheels[selected_wheel].wheel_max_edges) {
      edge_counter = 0;
    }
  }
  else
  {
    if (edge_counter == 0)
      edge_counter = triggerPattern.Wheels[selected_wheel].wheel_max_edges;
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

void loop() 
{
  uint16_t tmp_rpm = 0;
  
  communicate(); 
  
  if(mode == POT_RPM)
  {
    if (adc0_read_complete == true)
    {
      adc0_read_complete = false;
      tmp_rpm = adc0 << TMP_RPM_SHIFT;
      if (tmp_rpm > TMP_RPM_CAP) 
      { 
        tmp_rpm = TMP_RPM_CAP; 
      }
      wanted_rpm = tmp_rpm;
      reset_new_OCR1A(tmp_rpm);
    }
  }

  

}

void reset_new_OCR1A(uint32_t new_rpm)
{
  uint32_t tmp;
  uint8_t bitshift;
  uint8_t tmp_prescaler_bits;
  tmp = (uint32_t)(8000000.0/(triggerPattern.Wheels[selected_wheel].rpm_scaler * (float)(new_rpm < 10 ? 10:new_rpm)));

  get_prescaler_bits(&tmp,&tmp_prescaler_bits,&bitshift);

  new_OCR1A = (uint16_t)(tmp >> bitshift); 
  prescaler_bits = tmp_prescaler_bits;
  reset_prescaler = true; 
}

uint8_t get_bitshift_from_prescaler(uint8_t *prescaler_bits)
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
void get_prescaler_bits(uint32_t *potential_oc_value, uint8_t *prescaler, uint8_t *bitshift)
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
