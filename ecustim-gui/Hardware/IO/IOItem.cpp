#include "IOItem.h"


IOItem::IOItem(QObject *parent) : QObject(parent)
{
}

int IOItem::setValue() const
{
    return setValue_;
}

void IOItem::setSetValue(int setValue)
{
    if (setValue == setValue_) return;
    setValue_ = setValue;

    qDebug() << "New set value:" << setValue_;
    setActualValue(setValue_);

    emit setValueChanged(setValue);
}

//
int IOItem::actualValue() const
{
    return actualValue_;
}

void IOItem::setActualValue(int actualValue)
{
    if (actualValue == actualValue_) return;
    actualValue_ = actualValue;
    emit actualValueChanged(actualValue);
}

//
int IOItem::address() const
{
    return address_;
}

void IOItem::setAddress(int address)
{
    if (address == address_) return;
    address_ = address;
    emit addressChanged(address);
}

//
bool IOItem::active() const
{
    return active_;
}

void IOItem::setActive(bool active)
{
    if (active == active_) return;
    active_ = active;
    emit activeChanged(active);
}
//
QString IOItem::description() const
{
    return description_;
}

void IOItem::setDescription(QString description)
{
    if (description == description_) return;
    description_ = description;
    emit descriptionChanged(description);
}
