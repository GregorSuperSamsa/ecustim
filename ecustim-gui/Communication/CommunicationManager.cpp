#include "CommunicationManager.h"
#include "Communication/RemoteDeviceItem.h"
#include <QtDebug>

#define DEBUG_LOG


CommunicationManager::CommunicationManager(QObject *parent) : QObject(parent),
    models(CONNECTION_TYPE_COUNT)
  //model(new Model())
{
    // TODO: Last used communication type should be read from user settings
    setConnectionType(USB_UART);

    setConnectionStatus(IDLE);
}

void CommunicationManager::send(const QByteArray& data)
{
    Q_UNUSED(data)
}

Model *CommunicationManager::remoteDeviceModel() const
{
    return models.at(connectionType()).data();
    //return  model.data();
}

void CommunicationManager::connect(const QString& connectionInfo)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << "Connection string:" << qPrintable(connectionInfo);
#endif

    communicator->connect(connectionInfo);
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
    QObject::connect(communicator.data(), &Communication::remoteDeviceDiscovered, this, &CommunicationManager::onRemoteDeviceDiscovered, Qt::UniqueConnection);
    QObject::connect(communicator.data(), &Communication::remoteDeviceDiscoveryFinished, this, &CommunicationManager::onRemoteDeviceDiscoveryFinished, Qt::UniqueConnection);
}

CommunicationManager::CONNECTION_STATUS CommunicationManager::connectionStatus() const
{
    return connectionStatus_;
}

void CommunicationManager::setConnectionStatus(CONNECTION_STATUS connectionStatus)
{
    if (connectionStatus_ == connectionStatus)
        return;

    connectionStatus_ = connectionStatus;
    emit connectionStatusChanged(connectionStatus_);
}

void CommunicationManager::findDevices()
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << connectionType();
#endif

    // Remove previously found remote devices
    models.at(connectionType())->clearAll();

    communicator->getRemoteDevices();
    setConnectionStatus(DISCOVERY_STARTED);
}

void CommunicationManager::onRemoteDeviceDiscovered(QSharedPointer<RemoteDeviceItem> item)
{
    if (item.isNull()) return;

    //model->insert(item);
    models.at(connectionType())->insert(item);
}

void CommunicationManager::onRemoteDeviceDiscoveryFinished()
{
    setConnectionStatus(DISCOVERY_FINISHED);
}
