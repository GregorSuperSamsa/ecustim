#include "Fifo.h"


Fifo::Fifo()
{
    reset();
}

void Fifo::push(uint8_t data)
{
    _buffer[_head] = data;

    if (_full)
    {
        _tail = (_tail + 1) % BUFFER_SIZE;
    }
    _head = (_head + 1) % BUFFER_SIZE;

    _full = (_head == _tail);
}

bool Fifo::pop(uint8_t *data)
{
    if (!data || empty()) 
    {
        return false;
    }

    *data = _buffer[_tail];
    
    _full = false;
    _tail = (_tail + 1) % BUFFER_SIZE;
    
    return true;
}

bool Fifo::empty() const
{
    return (_head == _tail) && !_full;
}

bool Fifo::full() const
{
    return _full;
}

void Fifo::reset()
{
    _head = 0;
    _tail = 0;
    _full = false;
}

void Fifo::debug_print(HardwareSerial &interface)
{
    interface.println("");
    
    // Head position
    interface.print("HEAD:");
    interface.println(_head, DEC);
    // Tail position
    interface.print("TAIL:");
    interface.println(_tail, DEC);
    // Buffer
    for(uint8_t i = 0; i < BUFFER_SIZE; ++i)
    {
        interface.print(_buffer[i], DEC);
        interface.print(" ");
    }
    
    interface.println("");
}