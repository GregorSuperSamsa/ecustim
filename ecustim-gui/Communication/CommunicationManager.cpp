#include "CommunicationManager.h"
#include "RemoteDeviceItem.h"
#include <QtDebug>


//#define DEBUG_LOG


CommunicationManager::CommunicationManager(QObject *parent)
    : QObject(parent)
    , _models(CONNECTION_TYPE_COUNT)
{
    // TODO: Last used communication type should be read from user settings
    setConnectionType(USB_UART);

    // Handle tx transmission
    QObject::connect(&_timer, &QTimer::timeout, this, &CommunicationManager::onTimeout);
    _timer.setInterval(PACKET_HANDLE_TIMEOUT_MS);
    _timer.start();
}

void CommunicationManager::send(const QByteArray& data)
{
    if (data.isEmpty())
    {
        return;
    }

    txPackets.enqueue(composeTxPacket(data));
}

void CommunicationManager::sendRaw(const QByteArray &rawData)
{
    if (rawData.isEmpty())
    {
        return;
    }

    txPackets.enqueue(rawData);
}

QByteArray CommunicationManager::composeTxPacket(const QByteArray &data) const
{
    QByteArray packet;

    if (data.isEmpty())
    {
        return packet;
    }

    // Escape any special bytes in the raw tx data
    for(const auto &byte : qAsConst(data))
    {
        if (Protocol::STX == (uint8_t)byte || Protocol::ETX == (uint8_t)byte || Protocol::DLE == (uint8_t)byte)
        {
                packet.append(Protocol::DLE);
        }
        packet.append(byte);
    }
    packet.prepend(Protocol::STX);
    packet.append(Protocol::ETX);

    return packet;
}

void CommunicationManager::onTimeout()
{
    if (!_communicator.isNull() && _communicator->isConnected() && !txPackets.isEmpty())
    {
        _communicator->send(txPackets.dequeue());
    }
}

void CommunicationManager::onReceived(QByteArray data)
{
    rxBuffer.append(data);

    QByteArray packet;

    bool stx = false;
    bool etx = false;
    bool dle = false;
    int parsedOffset = 0;
    int currentOffset = 0;


    for (const auto &byte : qAsConst(rxBuffer))
    {
        currentOffset++;

        // Packet start flag
        if (!stx)
        {
            stx = Protocol::STX == (uint8_t)byte && !dle;
            if (stx)
            {
                packet.clear();
                continue;
            }
        }

        // Packet end flag
        if (!etx)
        {
            etx = Protocol::ETX == (uint8_t)byte && stx && !dle;
            if (etx)
            {
                if (packet.size() > 1)
                {
                    emit received(packet);
                }

                parsedOffset = currentOffset;
                stx = false;
                etx = false;
                continue;
            }
        }

        // Packet escape flag
        dle = Protocol::DLE == (uint8_t)byte && !dle;
        if (dle)
        {
            continue;
        }

        // Packet data
        if (stx)
        {
            packet.push_back(byte);
        }
    }

    // Remove already proccessed raw data
    rxBuffer.remove(0, parsedOffset);
}

Model *CommunicationManager::remoteDeviceModel() const
{
    return _models.at(connectionType()).data();
}

void CommunicationManager::connect(const QString& connectionInfo)
{
#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
    qDebug() << "Connection string:" << qPrintable(connectionInfo);
#endif

    _communicator->connect(connectionInfo);
}

void CommunicationManager::disconnect()
{
#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
#endif

    _communicator->disconnect();
}

CommunicationManager::CONNECTION_TYPE CommunicationManager::connectionType() const
{
    return _connectionType;
}

void CommunicationManager::setConnectionType(CONNECTION_TYPE connectionType)
{
    if (_connectionType == connectionType) return;

    _connectionType = connectionType;

    emit connectionTypeChanged(connectionType);

    switch (connectionType)
    {
    case USB_UART:
        _communicator.reset(new Uart());
        break;
    case BLUETOOTH:
        _communicator.reset(new Bluetooth());
        break;
    case CONNECTION_TYPE_UNKNOWN:
    case CONNECTION_TYPE_COUNT:
    default:
        return;
    }

    //
    if (_models[connectionType].isNull())
    {
        _models[connectionType].reset(new Model());
    }
    emit remoteDeviceModelChanged();

    //
    _communicator->initialize();

    // Connection
    QObject::connect(_communicator.data(), &Communication::remoteDeviceDiscovered, this, &CommunicationManager::onRemoteDeviceDiscovered, Qt::QueuedConnection);
    QObject::connect(_communicator.data(), &Communication::remoteDeviceDiscoveryFinished, this, &CommunicationManager::remoteDeviceDiscoveryFinished, Qt::QueuedConnection);
    //
    QObject::connect(_communicator.data(), &Communication::remoteDeviceConnected, this, &CommunicationManager::onRemoteDeviceConnected, Qt::QueuedConnection);
    QObject::connect(_communicator.data(), &Communication::remoteDeviceDisconnected, this, &CommunicationManager::onRemoteDeviceDisconnected, Qt::QueuedConnection);
    // Data handling
    QObject::connect(_communicator.data(), &Communication::received, this, &CommunicationManager::onReceived, Qt::UniqueConnection);

}

void CommunicationManager::startRemoteDeviceDiscovery()
{
#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
#endif

    // Remove previously found remote devices
    _models.at(connectionType())->clearAll();

    _communicator->startRemoteDeviceDiscovery();
}

void CommunicationManager::stopRemoteDeviceDiscovery()
{
#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
#endif

    _communicator->stopRemoteDeviceDiscovery();
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

    _models.at(connectionType())->insert(item);
}

void CommunicationManager::onRemoteDeviceConnected(QString connectionInfo)
{
#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
    qDebug() << "Connection info:" << qPrintable(connectionInfo);
#endif

    for (int i = 0; i < _models.at(connectionType())->count(); ++i)
    {
        auto remote = qSharedPointerDynamicCast<RemoteDeviceItem>(_models.at(connectionType())->data(i));
        if (!remote.isNull() && remote->connectionString() == connectionInfo)
        {
            remote->setConnectionState(RemoteDeviceItem::CONNECTED);
        }
    }
}

void CommunicationManager::onRemoteDeviceDisconnected(QString connectionInfo)
{
#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
    qDebug() << "Connection info:" << qPrintable(connectionInfo);
#endif

    for (int i = 0; i < _models.at(connectionType())->count(); ++i)
    {
        auto remote = qSharedPointerDynamicCast<RemoteDeviceItem>(_models.at(connectionType())->data(i));
        if (!remote.isNull() && remote->connectionString() == connectionInfo)
        {
            remote->setConnectionState(RemoteDeviceItem::UNCONNECTED);
            break;
        }
    }
}
