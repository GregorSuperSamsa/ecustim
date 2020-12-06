/*
 * Arbritrary wheel pattern generator wheel definitions
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
#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__


#include <Arduino.h>


// Wheel pattern structure:
//   decoder_name    - pointer to friendly name string;
//   edge_states_ptr - pointer to edge array;
//   rpm_scaler      - RPM scaler;
//   wheel_max_edges - number of edges in the array;
//   wheel_degrees   - whether the number of edges covers 360 or 720 degrees;
typedef struct _wheels wheels;
struct _wheels 
{
  const char *decoder_name PROGMEM;
  const unsigned char *edge_states_ptr PROGMEM;
  const float rpm_scaler;
  const uint16_t wheel_max_edges;
  const uint16_t wheel_degrees;
};


#endif
