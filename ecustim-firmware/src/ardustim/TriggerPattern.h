#ifndef __TRIGGER_PATTERN_H__
#define __TRIGGER_PATTERN_H__

#include <Arduino.h>
#include "wheel_defs.h"


class TriggerPattern
{
public:
    TriggerPattern();
    
    static void timer1Handler();
    
    
    void begin();
    //
    void setCurrent(const uint8_t &index);
    uint8_t current() const;
    //
    void setRpm(const uint32_t &rpm);
    uint32_t rpm() const;
    //
    enum ROTATION
    {
        CLOCKWISE = 0, 
        COUNTERCLOCKWISE = 1
    };
    void setRotation(const TriggerPattern::ROTATION &rotation);
    TriggerPattern::ROTATION rotation() const;
    //
    const char *name() const;

private:
    static volatile ROTATION _rotation;
    static volatile uint8_t _current_index;
    static uint32_t _rpm;

    //////////////////////////////////////////////////

    
    static volatile uint8_t output_invert_mask;
    static volatile uint8_t prescaler_bits;
    static volatile uint8_t last_prescaler_bits;
    static volatile uint8_t mode;
    static volatile uint16_t new_OCR1A; 
    //static volatile uint16_t edge_counter;
    //static volatile bool normal;
    static          uint16_t wanted_rpm;   
    static volatile bool reset_prescaler;
    
    static const uint8_t PATTERNS_COUNT = MAX_WHEELS;
     const _wheels *_patterns = Wheels;

    static void reset_new_OCR1A(uint32_t new_rpm);
    uint8_t get_bitshift_from_prescaler(uint8_t *prescaler_bits);
    void get_prescaler_bits(uint32_t *potential_oc_value, uint8_t *prescaler, uint8_t *bitshift);
   
};

extern TriggerPattern triggerPattern;

#endif
