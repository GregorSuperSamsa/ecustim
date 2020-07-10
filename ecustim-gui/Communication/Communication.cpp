#include "Communication.h"
#include <QSharedPointer>

Communication::Communication(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QList<QSharedPointer<RemoteDeviceItem>>>("QList<QSharedPointer<DeviceItem>>");
}
