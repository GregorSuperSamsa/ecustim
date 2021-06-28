#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

// Point to point protocol brief description
// https://eli.thegreenplace.net/2009/08/12/framing-in-serial-communications/

#include <Arduino.h>

namespace FrameByte
{
  // Acknowledge
  static const uint8_t ACK = 0x06;
  // Negative acknowledge
  static const uint8_t NAK = 0x15;
  // Start of text (packet)
  static const uint8_t STX = 0xAF;
  // End of text (packet)IOf
  static const uint8_t ETX = 0xAB;
  // Data link escape
  static const uint8_t DLE = 0xAC;
 
}

namespace Operation
{
  static const uint8_t READ = 0xAD;
  static const uint8_t WRITE = 0xAE;
}

namespace Command
{
  // Trigger Pattern Commands
  static const uint8_t TRIGGER_PATTERN_CMD_MASK = 0xA0;
  static const uint8_t TRIGGER_PATTERN_INDEX    = 0xA1;
  static const uint8_t TRIGGER_PATTERN_NAME     = 0xA2;
  static const uint8_t TRIGGER_PATTERN_DATA     = 0xA3;
  static const uint8_t TRIGGER_PATTERN_DEGREES  = 0xA4;
  static const uint8_t TRIGGER_PATTERN_ROTATION = 0xA5;
  static const uint8_t TRIGGER_PATTERN_RPM      = 0xA6;
  static const uint8_t TRIGGER_PATTERN_COUNT    = 0xA7;
  static const uint8_t TRIGGER_PATTERN_ENABLE   = 0xA8;
}


#endif