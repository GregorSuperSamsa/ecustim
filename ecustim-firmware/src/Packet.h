#ifndef __PACKET_H__
#define __PACKET_H__

#include <Arduino.h>
#include "Protocol.h"


class Packet
{
private:
    uint8_t* _p_data_buffer = nullptr;
    uint16_t _max_data_buffer_size = 0;
    uint16_t _data_bytes_count = 0;
    
    bool _has_command = false;
    uint8_t _command = 0;
    
    bool _has_operation = false;
    uint8_t _operation = 0;
    
    bool _has_hardware_index = false;
    uint8_t _hardware_index = 0;

public:
    Packet(uint8_t* p_data_buffer, uint16_t data_buffer_size);

    uint8_t commandType() const;
    
    void setCommand(uint8_t command);
    uint8_t command() const;
    
    void setOperation(uint8_t operation);
    uint8_t operation() const;
    

    void setHardwareIndex(uint8_t index);
    uint8_t hardwareIndex() const;
    
    bool appendData(const void* p_source_bytes, const uint16_t source_bytes_count, const bool is_source_progmem = false);

    bool getData(uint8_t* p_data_buffer, uint16_t* data_bytes_count);
    uint8_t* getDataPointer();
    uint16_t getDataBytesCount() const;

    void reset();
    bool pending() const;
};

#endif
