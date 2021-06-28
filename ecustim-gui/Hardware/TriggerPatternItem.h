#ifndef TRRIGER_PATTERN_ITEM_H
#define TRRIGER_PATTERN_ITEM_H

#include "HardwareItem.h"


class TriggerPatternItem: public HardwareItem
{
    Q_OBJECT

    Q_PROPERTY(QVector<int> pattern READ pattern WRITE setPattern NOTIFY patternChanged);

public:
    TriggerPatternItem(QObject *parent = nullptr);

    void setPattern(QVector<int> data);
    QVector<int> pattern() const;

private:
    QVector<int> _pattern;

signals:
    void patternChanged(QVector<int> pattern);

};

#endif // TRRIGER_PATTERN_ITEM_H
