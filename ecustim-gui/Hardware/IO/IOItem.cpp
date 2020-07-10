#include "IOItem.h"


Item::Item(QObject *parent):QObject(parent)
{

}

int Item::setValue() const
{
    return setValue_;
}

void Item::setSetValue(int setValue)
{
    if (setValue == setValue_) return;
    setValue_ = setValue;

    qDebug() << "New set value:" << setValue_;
    setActualValue(setValue_);

    emit setValueChanged(setValue);
}

//
int Item::actualValue() const
{
    return actualValue_;
}

void Item::setActualValue(int actualValue)
{
    if (actualValue == actualValue_) return;
    actualValue_ = actualValue;
    emit actualValueChanged(actualValue);
}

//
int Item::address() const
{
    return address_;
}

void Item::setAddress(int address)
{
    if (address == address_) return;
    address_ = address;
    emit addressChanged(address);
}

//
bool Item::active() const
{
    return active_;
}

void Item::setActive(bool active)
{
    if (active == active_) return;
    active_ = active;
    emit activeChanged(active);
}
//
QString Item::description() const
{
    return description_;
}

void Item::setDescription(QString description)
{
    if (description == description_) return;
    description_ = description;
    emit descriptionChanged(description);
}
