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

#include "defines.h"
#include "ardustim.h"
#include "enums.h"
#include "comms.h"
#include "structures.h"
#include "storage.h"
#include "wheel_defs.h"
#include "user_defaults.h"


extern wheels Wheels[];

// Volatile variables (USED in ISR's)
volatile uint8_t selected_wheel;
extern volatile bool normal;
extern volatile uint16_t edge_counter;
extern volatile uint16_t new_OCR1A;
extern volatile uint32_t oc_remainder;

bool cmdPending;
byte currentCommand;
uint16_t numTeeth;

// Initialize serial communication
void setup_serial()
{
  Serial.begin(115200);
  while (!Serial) {}

  // Serial.println("Ecustim 0.1");
  cmdPending = false;
}

void communicate()
{
  if (!Serial.available())
  {
    return;
  }

  char buf[80];
  byte tmp_wheel;
  byte tmp_mode;

  if (cmdPending == false)
  {
    currentCommand = Serial.read();
  }

  //cmdPending = true;

  switch (currentCommand)
  {
  case 'a':
    break;

  // Set the fixed RPM value
  case 'f':
    mode = FIXED_RPM;
    // Wait for the new RPM bytes
    while (Serial.available() < 2)
    {
    }

    wanted_rpm = word(Serial.read(), Serial.read());

    setRPM(wanted_rpm);
    break;

  // Save the current config
  case 'c':
    saveConfig();
    break;

  // Send the list of wheel names
  case 'L':
    for (byte x = 0; x < MAX_WHEELS; x++)
    {
      strcpy_P(buf, Wheels[x].decoder_name);
      Serial.println(buf);
    }
    break;

  // Change the RPM mode
  case 'M':
    // Wait for the new mode byte
    while (Serial.available() < 1)
    {
    }
    tmp_mode = Serial.read();

    if (tmp_mode <= POT_RPM)
    {
      mode = tmp_mode;
    }
    break;

  // Send the number of wheels
  case 'n':
    Serial.println(MAX_WHEELS);
    break;

  // Send the number (index) of the current wheel
  case 'N':
    Serial.println(selected_wheel);
    break;

  // Send the size of the current wheel
  case 'p':
    Serial.println(Wheels[selected_wheel].wheel_max_edges);
    break;

  // Send the pattern for the current wheel
  case 'P':
    numTeeth = pgm_read_word(Wheels[selected_wheel].wheel_max_edges);

    for (uint16_t x = 0; x < Wheels[selected_wheel].wheel_max_edges; ++x)
    {
      if (x != 0)
      {
        Serial.print(",");
      }

      byte tempByte = pgm_read_byte(&Wheels[selected_wheel].edge_states_ptr[x]);
      Serial.print(tempByte);
    }
    Serial.println("");
    // 2nd row of data sent is the number of degrees the wheel runs over (360 or 720 typically)
    Serial.println(Wheels[selected_wheel].wheel_degrees);
    break;

  // Send the current RPM
  case 'R':
    Serial.println(wanted_rpm);
    break;

  // Set the current wheel
  case 'S':
    while (Serial.available() < 1)
    {
    }
    tmp_wheel = Serial.read();
    if (tmp_wheel < MAX_WHEELS)
    {
      selected_wheel = tmp_wheel;
      display_new_wheel();
    }
    break;

  // Just a test method for switching the to the next wheel
  case 'X':
    select_next_wheel_cb();
    strcpy_P(buf, Wheels[selected_wheel].decoder_name);
    Serial.println(buf);
    break;

  default:
    break;
  }

  cmdPending = false;
}

void display_new_wheel()
{
  reset_new_OCR1A(wanted_rpm);

  // Reset to beginning of the wheel pattern
  edge_counter = 0;

  // if (mode != LINEAR_SWEPT_RPM)
  //   reset_new_OCR1A(wanted_rpm);
  // else
  //   compute_sweep_stages(&sweep_low_rpm, &sweep_high_rpm);
  // edge_counter = 0; // Reset to beginning of the wheel pattern */
}

// Selects the next wheel, if at the end, wrap to the beginning of the list,
// re-calculate the OCR1A value (RPM) and reset, return user information on the
// selected wheel and current RPM
void select_next_wheel_cb()
{
  if (selected_wheel == (MAX_WHEELS - 1))
    selected_wheel = 0;
  else
    selected_wheel++;

  display_new_wheel();
}

// Changes the RPM based on user input
//
// Prompts user for new RPM, reads it, validates it's within range, sets lock to
// prevent a race condition with the sweeper, free's memory of SweepSteps
// structure IF allocated, sets the mode to fixed RPM, recalculates the new OCR1A
// value based on the user specificaed RPM and sets it and then removes the lock
void setRPM(uint32_t newRPM)
{
  if (newRPM < 10)
  {
    return;
  }

  reset_new_OCR1A(newRPM);

  wanted_rpm = newRPM;
}

// Figures out the amount of free RAM remaining and returns it to the caller
// \return amount of free memory
uint16_t freeRam()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}