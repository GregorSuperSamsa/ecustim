#ifndef IO_ITEM_H
#define IO_ITEM_H

#include "HardwareItem.h"


class IOItem: public HardwareItem
{
    Q_OBJECT

    Q_PROPERTY(int address READ address WRITE setAddress NOTIFY addressChanged)

public:
    IOItem(QObject *parent = nullptr);

    void setAddress(int address);
    int address() const;

private:
    int _address;

signals:
    void addressChanged(int address);

};

#endif // IO_ITEM_H
