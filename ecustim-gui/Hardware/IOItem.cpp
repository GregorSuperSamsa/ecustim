#include "IOItem.h"


IOItem::IOItem(QObject *parent) : HardwareItem(parent)
{
}

void IOItem::setAddress(int address)
{
    if (address == _address) return;

    _address = address;

    emit addressChanged(address);
}

int IOItem::address() const
{
    return _address;
}
