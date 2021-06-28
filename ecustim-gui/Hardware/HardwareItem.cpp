#include "HardwareItem.h"


HardwareItem::HardwareItem(QObject *parent) : QObject(parent)
{
}

void HardwareItem::setValue(int value)
{
    if (value == _value) return;

    _value = value;

    emit valueChanged(value);
}

int HardwareItem::value() const
{
    return _value;
}

void HardwareItem::setActive(bool active)
{
    if (active == _active) return;

    _active = active;

    emit activeChanged(active);
}

bool HardwareItem::active() const
{
    return _active;
}

void HardwareItem::setDescription(QString description)
{
    if (description == _description) return;

    _description = description;

    emit descriptionChanged(description);
}

QString HardwareItem::description() const
{
    return _description;
}

