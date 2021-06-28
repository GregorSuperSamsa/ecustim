/*
 * A simple implementation of FIFO queue
 */
#ifndef __FIFO_H__
#define __FIFO_H__

#include <Arduino.h>


class Fifo
{
public:
    Fifo();

    void push(uint8_t data);

    bool pop(uint8_t *data);

    void reset();

    bool empty() const;
    bool full() const;
       
    void debug_print(HardwareSerial &interface);
private:
    static const uint8_t BUFFER_SIZE = 0xFF;

    uint8_t _buffer[BUFFER_SIZE];

    uint8_t _head;
    uint8_t _tail;
    bool _full;
};




#endif 