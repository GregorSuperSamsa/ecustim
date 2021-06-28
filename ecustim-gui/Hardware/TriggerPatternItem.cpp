#include "TriggerPatternItem.h"


TriggerPatternItem::TriggerPatternItem(QObject *parent): HardwareItem(parent)
{
}

void TriggerPatternItem::setPattern(QVector<int> pattern)
{
    if (pattern == _pattern) return;

    _pattern = pattern;

    emit patternChanged(pattern);
}

QVector<int> TriggerPatternItem::pattern() const
{
    return _pattern;
}
