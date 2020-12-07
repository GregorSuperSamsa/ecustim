#include "TriggerPattern.h"


void TriggerPattern::setup()
{

}

void TriggerPattern::setPattern(const uint8_t &index)
{
    if (_index != index)
    {
        _index = index;
    }
}
uint8_t TriggerPattern::pattern() const
{
    return _index;
}

void TriggerPattern::setRpm(const uint16_t &rpm)
{
    if (_rpm != rpm)
    {
        _rpm = rpm;
    }
}

uint16_t TriggerPattern::rpm() const
{
    return _rpm;
}

TriggerPattern triggerPattern;