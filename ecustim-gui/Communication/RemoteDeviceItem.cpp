#include "RemoteDeviceItem.h"

RemoteDeviceItem::RemoteDeviceItem(QObject *parent) : QObject(parent)
{
    setConnectionState(UNCONNECTED);
}
