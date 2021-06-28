#include "Packet.h"


Packet::Packet(uint8_t* p_data_buffer, uint16_t data_buffer_size)
{
    _p_data_buffer = p_data_buffer;
    _max_data_buffer_size = data_buffer_size;
}

uint8_t Packet::commandType() const
{
    //return (_command >> 4) & 0x0F;
    return (_command & 0xF0);
}

void Packet::setCommand(uint8_t command)
{
    _command = command;
    _has_command = true;
}

uint8_t Packet::command() const
{
    return _command;
}

void Packet::setOperation(uint8_t operation)
{
    _operation = operation;
    _has_operation = true;
}

uint8_t Packet::operation() const
{
    return _operation;
}

void Packet::setHardwareIndex(uint8_t index)
{
    _hardware_index = index;
    _has_hardware_index = true;
}

uint8_t Packet::hardwareIndex() const
{
    return _hardware_index;
}

bool Packet::appendData(const void* p_source_bytes, const uint16_t source_bytes_count, const bool is_source_progmem)
{
    if (p_source_bytes == nullptr || (source_bytes_count + _data_bytes_count) > _max_data_buffer_size)
    {
        return false;
    }

    if (is_source_progmem)
    {
        if (nullptr == memcpy_P(&_p_data_buffer[_data_bytes_count], p_source_bytes, source_bytes_count))
        {
            return false;
        }
    }
    else
    {
        if (nullptr == memcpy(&_p_data_buffer[_data_bytes_count], p_source_bytes, source_bytes_count))
        {
            return false;
        }

    }

    _data_bytes_count += source_bytes_count;

    return true;
}

uint8_t* Packet::getDataPointer()
{
    return _p_data_buffer;
}

uint16_t Packet::getDataBytesCount() const
{
    return _data_bytes_count;
}

bool Packet::getData(uint8_t* p_data_buffer, uint16_t* data_bytes_count)
{
    if (_p_data_buffer == nullptr || _data_bytes_count == 0)
    {
        return false;
    }

    p_data_buffer = _p_data_buffer;
    *data_bytes_count = _data_bytes_count;

    return true;
}

void Packet::reset()
{
    _has_command = false;
    _has_operation = false;
    _has_hardware_index = false;
        
    _data_bytes_count = 0;
}

bool Packet::pending() const
{
    return _has_command && _has_operation && _has_hardware_index;
}