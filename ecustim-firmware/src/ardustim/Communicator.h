#ifndef __COMMUNICATOR_H__
#define __COMMUNICATOR_H__

#include <Arduino.h>
#include "Protocol.h"
#include "Packet.h"

class Communicator
{
private:
    static const unsigned long UART_BAUD_RATE = 115200;
    static const unsigned long BLUETOOTH_BAUD_RATE = 115200;
    
    bool isEscapable(uint8_t byte);

    void read(HardwareSerial &interface);
    void write(HardwareSerial &interface);   

    // Uart
    HardwareSerial &uart = Serial;
    // Bluetooth, on Mega, Serial2 is used (pins 16, 17)
    HardwareSerial &bluetooth = Serial2;

    Packet* rx;
    Packet* tx;

public:
    Communicator(Packet* rx, Packet* tx);

    void begin();
    void processCommands();
};

#endif
