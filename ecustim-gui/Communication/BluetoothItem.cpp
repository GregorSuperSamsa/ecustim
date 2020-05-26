#include "BluetoothItem.h"


BluetoothItem::BluetoothItem(QObject *parent) : QObject(parent)
{

}

void BluetoothItem::setName(QString name)
{
    if (name_ == name) return;

    name_ = name;
    emit nameChanged(name_);
}

QString BluetoothItem::name() const
{
    return name_;
}

void BluetoothItem::setAddress(QString address)
{
    if (address_ == address) return;

    address_ = address;
    emit addressChanged(address_);
}

QString BluetoothItem::address() const
{
    return address_;
}

void BluetoothItem::setRssi(QString rssi)
{
    if (rssi_ == rssi) return;

    rssi_ = rssi;
    emit rssiChanged(rssi_);
}

QString BluetoothItem::rssi() const
{
    return rssi_;
}


