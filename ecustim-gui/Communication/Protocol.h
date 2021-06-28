#ifndef PROTOCOL_H
#define PROTOCOL_H


#include <QtGlobal>
#include <QByteArray>


namespace Protocol
{

enum MESSAGE_TYPE
{
    VARIABLE_OUTPUT = 0,
    SWITCHABLE_INPUT,
    SWITCHABLE_OUTPUT,
    TRIGGER
};

// Acknowledge
static const uint8_t ACK = 0x06;
// Negative acknowledge
static const uint8_t NAK = 0x15;
// Start of text (packet)
static const uint8_t STX = 0xAF;
// End of text (packet)
static const uint8_t ETX = 0xAB;
// Data link escape
static const uint8_t DLE = 0xAC;


namespace Command
{
static const uint8_t READ_HW_CAPABILITIES = 0x01;
struct Trigger
{
  static const uint8_t selected = 0x02;
  static const uint8_t edges_counts = 0x03;
  static const uint8_t degrees = 0x04;
  static const uint8_t name = 0x05;
  static const uint8_t pattern = 0x06;
};
static const Trigger trigger_cmd;

}

}

#endif // PROTOCOL_H
