#ifndef __TRIGGER_PATTERN_H__
#define __TRIGGER_PATTERN_H__

#include <Arduino.h>
#include "Packet.h"
#include "wheel_defs.h"

class TriggerPattern
{
public:
    TriggerPattern(Packet *rx, Packet *tx);
    void begin();
    void processCommands();

    static void timer1Handler();

    static const uint8_t PATTERNS_COUNT = MAX_WHEELS;
    

private:
    Packet *rx = nullptr;
    Packet *tx = nullptr;
    static TriggerPattern* triggerPattern;
    

    static volatile uint8_t pattern_index;
    //
    static uint16_t rpm;
    static const uint8_t min_rpm = 10;
    static const uint16_t max_rpm = 10000;
    //
    bool enabled = true;
    //
    enum ROTATION_DIRECTION
    {
        CLOCKWISE = 0,
        COUNTERCLOCKWISE = 1
    };
    static volatile ROTATION_DIRECTION rotation_direction;


    void processCommandIndex();
    void processCommandName();
    void processCommandData();
    void processCommandDegrees();
    void processCommandRotation();
    void processCommandRpm();
    void processCommandCount();
    void processCommandEnable();

    //////////////////////////////////////////////////

    static volatile uint8_t prescaler_bits;
    static volatile uint8_t last_prescaler_bits;
    static volatile uint16_t new_OCR1A;
    static uint16_t wanted_rpm;
    static volatile bool reset_prescaler;

    const _wheels *_patterns = Wheels;

    static void reset_new_OCR1A(uint32_t new_rpm);
    uint8_t get_bitshift_from_prescaler(uint8_t *prescaler_bits);
    void get_prescaler_bits(uint32_t *potential_oc_value, uint8_t *prescaler, uint8_t *bitshift);
};

#endif
