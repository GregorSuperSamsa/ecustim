#include "SerialItem.h"


SerialItem::SerialItem(QObject *parent) : QObject(parent)
{

}

// Port Name
void SerialItem::setName(QString name)
{
    if (name_ == name) return;

    name_ = name;
    emit nameChanged(name_);
}

QString SerialItem::name() const
{
    return name_;
}

// Port Location on the Bus
void SerialItem::setLocation(QString location)
{
    if (location_ == location) return;

    location_ = location;
    emit locationChanged(location_);
}

QString SerialItem::location() const
{
    return location_;
}

// Port Description
void SerialItem::setDescription(QString description)
{
    if (description_ == description) return;

    description_ = description;
    emit descriptionChanged(description_);
}

QString SerialItem::description() const
{
    return description_;
}

// Manufacturer
void SerialItem::setManufacturer(QString manufacturer)
{
    if (manufacturer_ == manufacturer) return;

    manufacturer_ = manufacturer;
    emit manufacturerChanged(manufacturer_);
}

QString SerialItem::manufacturer() const
{
    return manufacturer_;
}

// Serial Number
void SerialItem::setSerialNumber(QString serialNumber)
{
    if (serialNumber_ == serialNumber) return;

    serialNumber_ = serialNumber;
    emit serialNumberChanged(serialNumber_);
}

QString SerialItem::serialNumber() const
{
    return serialNumber_;
}

// Vendor Id
void SerialItem::setVendorId(QString vendorId)
{
    if (vendorId_ == vendorId) return;

    vendorId_ = vendorId;
    emit vendorIdChanged(vendorId_);
}

QString SerialItem::vendorId() const
{
    return vendorId_;
}

// Product Id
void SerialItem::setProductId(QString productId)
{
    if (productId_ == productId) return;

    productId_ = productId;
    emit productIdChanged(productId_);
}

QString SerialItem::productId() const
{
    return productId_;
}
