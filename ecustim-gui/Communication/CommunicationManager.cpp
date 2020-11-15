#include "CommunicationManager.h"
#include "Communication/RemoteDeviceItem.h"
#include <QtDebug>

#define DEBUG_LOG


CommunicationManager::CommunicationManager(QObject *parent) : QObject(parent),
    models(CONNECTION_TYPE_COUNT)
{
    // TODO: Last used communication type should be read from user settings
    setConnectionType(USB_UART);
}

void CommunicationManager::send(const QByteArray& data)
{
    Q_UNUSED(data)
}

Model *CommunicationManager::remoteDeviceModel() const
{
    return models.at(connectionType()).data();
}

void CommunicationManager::connect(const QString& connectionInfo)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << "Connection string:" << qPrintable(connectionInfo);
#endif

    communicator->connect(connectionInfo);
}

void CommunicationManager::disconnect()
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
#endif

    communicator->disconnect();
}

CommunicationManager::CONNECTION_TYPE CommunicationManager::connectionType() const
{
    return connectionType_;
}

void CommunicationManager::setConnectionType(CONNECTION_TYPE connectionType)
{
    if (connectionType_ == connectionType)
        return;

    connectionType_ = connectionType;
    emit connectionTypeChanged(connectionType_);

    switch (connectionType) {
    case USB_UART:
        communicator.reset(new Uart());
        break;
    case BLUETOOTH:
        communicator.reset(new Bluetooth());
        break;
    case CONNECTION_TYPE_UNKNOWN:
    case CONNECTION_TYPE_COUNT:
    default:
        return;
    }

    //
    if (models[connectionType].isNull()) {
        models[connectionType].reset(new Model());
    }
    emit remoteDeviceModelChanged();

    //
    communicator->initialize();
    QObject::connect(communicator.data(), &Communication::remoteDeviceDiscovered, this, &CommunicationManager::onRemoteDeviceDiscovered, Qt::QueuedConnection);
    QObject::connect(communicator.data(), &Communication::remoteDeviceDiscoveryFinished, this, &CommunicationManager::remoteDeviceDiscoveryFinished, Qt::QueuedConnection);
    //
    QObject::connect(communicator.data(), &Communication::remoteDeviceConnected, this, &CommunicationManager::onRemoteDeviceConnected, Qt::QueuedConnection);
    QObject::connect(communicator.data(), &Communication::remoteDeviceDisconnected, this, &CommunicationManager::onRemoteDeviceDisconnected, Qt::QueuedConnection);
}

void CommunicationManager::startRemoteDeviceDiscovery()
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
#endif

    // Remove previously found remote devices
    models.at(connectionType())->clearAll();

    communicator->startRemoteDeviceDiscovery();
}

void CommunicationManager::stopRemoteDeviceDiscovery()
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
#endif

    communicator->stopRemoteDeviceDiscovery();
}

void CommunicationManager::onRemoteDeviceDiscovered(QSharedPointer<RemoteDeviceItem> item)
{
    if (item.isNull()) return;

//    QObject::connect(item.data(), &RemoteDeviceItem::connectionStateChanged, [=]()
//    {
//        if (item->connectionState() == RemoteDeviceItem::CONNECTING)
//        {
//            connect(item->connectionString());
//        }
//        else if (item->connectionState() == RemoteDeviceItem::DISCONNECTING)
//        {
//            disconnect();
//        }
//    });

    models.at(connectionType())->insert(item);
}

void CommunicationManager::onRemoteDeviceConnected(QString connectionInfo)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << "Connection info:" << qPrintable(connectionInfo);
#endif

    for (int i = 0; i < models.at(connectionType())->count(); ++i)
    {
        auto remote = qSharedPointerDynamicCast<RemoteDeviceItem>(models.at(connectionType())->data(i));
        if (!remote.isNull() && remote->connectionString() == connectionInfo)
        {
            remote->setConnectionState(RemoteDeviceItem::CONNECTED);
        }
    }
}

void CommunicationManager::onRemoteDeviceDisconnected(QString connectionInfo)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << "Connection info:" << qPrintable(connectionInfo);
#endif

    for (int i = 0; i < models.at(connectionType())->count(); ++i)
    {
        auto remote = qSharedPointerDynamicCast<RemoteDeviceItem>(models.at(connectionType())->data(i));
        if (!remote.isNull() && remote->connectionString() == connectionInfo)
        {
            remote->setConnectionState(RemoteDeviceItem::UNCONNECTED);
            break;
        }
    }
}


