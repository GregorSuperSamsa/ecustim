#include "Bluetooth.h"
#include <QDebug>
#include <QThread>
#include <QCoreApplication>


#define DEBUG_LOG


const Bluetooth::DISCOVERY_TYPE Bluetooth::discoveryType = DISCOVERY_TYPE_DEVICE;

Bluetooth::Bluetooth(QObject *parent): Communication(parent),
    localDevice(new QBluetoothLocalDevice(this)),
    deviceAgent(new QBluetoothDeviceDiscoveryAgent(this)),
    serviceAgent(new QBluetoothServiceDiscoveryAgent(this)),
    socket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this))
{
}

Bluetooth::~Bluetooth()
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
#endif
    stopRemoteDeviceDiscovery();
    disconnect();
}

// Initialize the communication interface
void Bluetooth::initialize()
{
    if (isValid())
    {
        // Stop any active discovery
        stopRemoteDeviceDiscovery();

        // Close any active connection
        disconnect();

        // Socket instance
        QObject::connect(socket.data(), &QBluetoothSocket::readyRead, this, &Bluetooth::onSocketReadyRead, Qt::UniqueConnection);
        QObject::connect(socket.data(), &QBluetoothSocket::stateChanged, this, &Bluetooth::onSocketStateChanged, Qt::UniqueConnection);
        QObject::connect(socket.data(), QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error), this, &Bluetooth::onSocketError, Qt::UniqueConnection);

        // Setup local device
        QObject::connect(localDevice.data(), &QBluetoothLocalDevice::hostModeStateChanged, this, &Bluetooth::onHostModeStateChanged, Qt::UniqueConnection);
        QObject::connect(localDevice.data(), &QBluetoothLocalDevice::deviceConnected, this, &Bluetooth::onDeviceConnected, Qt::UniqueConnection);
        QObject::connect(localDevice.data(), &QBluetoothLocalDevice::deviceDisconnected, this, &Bluetooth::onDeviceDisconnected, Qt::UniqueConnection);
        localDevice->powerOn();
        localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);

        // Setup device discovery
        initializeRemoteDeviceDiscovery();
    }
}

// Check whether the communication interface is valid on this host
bool Bluetooth::isValid() const
{
    return (!localDevice.isNull() && localDevice->isValid());
}

// Connect to a selected remote device
void Bluetooth::connect(const QString& connectionInfo)
{
    if (connectionInfo.isEmpty())
        return;

    if (isValid())
    {
#ifdef DEBUG_LOG
        qDebug() << endl << __PRETTY_FUNCTION__;
        qDebug() << "Device address:" << qPrintable(connectionInfo);
#endif
        // Stop any active discovery
        stopRemoteDeviceDiscovery();

        // If has previous connection, disconnect
        disconnect();
        //
        socket->connectToService(QBluetoothAddress(connectionInfo), QBluetoothUuid::SerialPort, QIODevice::ReadWrite);
    }
}

// Disconnect from remote device
void Bluetooth::disconnect()
{
    const int RETRIES_MAX_COUNT = 10;
    const int RETRY_TIMEOUT_MS = 100;
    const int UNCONNECTED_TIMEOUT_MS = 5 * 100;

    if (isConnected())
    {
        // Try disconnecting gracefully
        socket->disconnectFromService();
        // Warning the code below blocks qt event loop
        return;


        // Wait for socket state
        int retries = RETRIES_MAX_COUNT;
        while(retries > 0)
        {
            retries--;
            QThread::msleep(RETRY_TIMEOUT_MS);

            if (QBluetoothSocket::UnconnectedState == socket->state())
            {
                QThread::msleep(UNCONNECTED_TIMEOUT_MS);
#ifdef DEBUG_LOG
                qDebug() << endl << __PRETTY_FUNCTION__;
                qDebug() << "Socket gracefully closed . . .";
#endif
                return;
            }
        }

        // Just in case we were unable to close the socket
        socket->abort();
#ifdef DEBUG_LOG
        qDebug() << endl << __PRETTY_FUNCTION__;
        qDebug() << "Socket aborted . . .";
#endif

    }
}

// Check whether we are currently connected to a remote device
bool Bluetooth::isConnected() const
{
    return (isValid() && !socket.isNull() && socket->isOpen());
}

// Start discovering currently available remote devices
void Bluetooth::startRemoteDeviceDiscovery()
{
    if (isValid())
    {
#ifdef DEBUG_LOG
        qDebug() << endl << __PRETTY_FUNCTION__;
#endif

        // Start device discovery
        if (!deviceAgent.isNull() && DISCOVERY_TYPE_DEVICE == discoveryType)
        {
            if (deviceAgent->isActive())
            {
                deviceAgent->stop();
            }
            deviceAgent->start();
        }
        // Start service discovery
        else if (!serviceAgent.isNull() && DISCOVERY_TYPE_SERVICE == discoveryType)
        {
            if (serviceAgent->isActive())
            {
                serviceAgent->stop();
            }
            serviceAgent->start(QBluetoothServiceDiscoveryAgent::FullDiscovery);
        }
        // Problem! There is no available discovery agent
        else
        {
            emit remoteDeviceDiscoveryFinished();
        }
    }
}

// Stop discovering currently available remote devices
void Bluetooth::stopRemoteDeviceDiscovery()
{
    // Stop device discovery, if active
    if (!deviceAgent.isNull() && deviceAgent->isActive())
    {
        deviceAgent->stop();
    }

    // Stop service discovery, if active
    if (!serviceAgent.isNull() && serviceAgent->isActive())
    {
        serviceAgent->stop();
    }
}

// Send raw data to the remote device
void Bluetooth::send(const QByteArray& bytes)
{
    Q_UNUSED(bytes)

    if (isConnected())
    {
        //
    }

}

void Bluetooth::initializeRemoteDeviceDiscovery()
{
    if (!isValid()) return;

    if (DISCOVERY_TYPE_DEVICE == discoveryType)
    {
        deviceAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
        QObject::connect(deviceAgent.data(), &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &Bluetooth::onDeviceDiscovered , Qt::UniqueConnection);
        QObject::connect(deviceAgent.data(), &QBluetoothDeviceDiscoveryAgent::finished, this, &Bluetooth::onDeviceDiscoveryFinished, Qt::UniqueConnection);
        QObject::connect(deviceAgent.data(), &QBluetoothDeviceDiscoveryAgent::canceled, this, &Bluetooth::onDeviceDiscoveryFinished, Qt::UniqueConnection);
    }
    // Setup service discovery
    else if (DISCOVERY_TYPE_SERVICE == discoveryType)
    {
        serviceAgent->setUuidFilter(QBluetoothUuid::SerialPort);
        QObject::connect(serviceAgent.data(), &QBluetoothServiceDiscoveryAgent::serviceDiscovered, this, &Bluetooth::onServiceDiscovered, Qt::UniqueConnection);
        QObject::connect(serviceAgent.data(), &QBluetoothServiceDiscoveryAgent::finished, this, &Bluetooth::onServiceDiscoveryFinished, Qt::UniqueConnection);
        QObject::connect(serviceAgent.data(), &QBluetoothServiceDiscoveryAgent::canceled, this, &Bluetooth::onServiceDiscoveryFinished, Qt::UniqueConnection);
    }
}

void Bluetooth::onServiceDiscovered(const QBluetoothServiceInfo &info)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << "Device name:   " << qPrintable(info.device().name());
    qDebug() << "Device address:" << qPrintable(info.device().address().toString());
    qDebug() << "RSSI:          " << info.device().rssi();
    qDebug() << "Service name:  " << info.serviceName();
    qDebug() << "Description:   " << info.attribute(QBluetoothServiceInfo::ServiceDescription).toString();
    qDebug() << "Provider:      " << info.attribute(QBluetoothServiceInfo::ServiceProvider).toString();
    qDebug() << "RFCOMM server channel:" << info.serverChannel();
    qDebug() << "L2CAP protocol service multiplexer:" << info.protocolServiceMultiplexer();
#endif

    emit remoteDeviceDiscovered(processRemoteDeviceInfo(info));
}

void Bluetooth::onServiceDiscoveryFinished()
{
    emit remoteDeviceDiscoveryFinished();
}

void Bluetooth::onDeviceDiscovered(const QBluetoothDeviceInfo &info)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << "Device name:   " << qPrintable(info.name());
    qDebug() << "Device address:" << qPrintable(info.address().toString());
    qDebug() << "RSSI:          " << info.rssi();
    QList<QBluetoothUuid> uuids  =  info.serviceUuids();
    for(QBluetoothUuid uuid: uuids)
        qDebug() << "UUID:          " << uuid.toString();
#endif

    emit remoteDeviceDiscovered(processRemoteDeviceInfo(info));
}

void Bluetooth::onDeviceDiscoveryFinished()
{
    emit remoteDeviceDiscoveryFinished();
}

void Bluetooth::onDeviceConnected(QBluetoothAddress address)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << "Device address:" << qPrintable(address.toString());
#endif

    emit remoteDeviceConnected(address.toString());
}

void Bluetooth::onDeviceDisconnected(QBluetoothAddress address)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << "Device address:" << qPrintable(address.toString());
#endif

    emit remoteDeviceDisconnected(address.toString());
}

QSharedPointer<RemoteDeviceItem> Bluetooth::processRemoteDeviceInfo(const QBluetoothServiceInfo &serviceInfo)
{
    if (!serviceInfo.isValid())
        return QSharedPointer<RemoteDeviceItem>(nullptr);


    QSharedPointer<RemoteDeviceItem> item(new RemoteDeviceItem);
    // Display text
    item->setDisplayText(serviceInfo.device().name() + "\n" + serviceInfo.device().address().toString());
    // Connection string
    item->setConnectionString(serviceInfo.device().address().toString());
    // Additional info
    QStringList additionalInfo;
    //
    additionalInfo << "RSSI:"           << QString::number(serviceInfo.device().rssi());
    //
    additionalInfo << "UUID:"           << serviceInfo.serviceUuid().toString();
    //
    additionalInfo << "Service name:"   << serviceInfo.serviceName();
    //
    additionalInfo << "Description:"    << serviceInfo.attribute(QBluetoothServiceInfo::ServiceDescription).toString();
    //
    additionalInfo << "Provider:"       << serviceInfo.attribute(QBluetoothServiceInfo::ServiceProvider).toString();
    //
    additionalInfo << "Remote server channel:" << QString::number(serviceInfo.serverChannel());

    item->setAdditionalInfo(additionalInfo);

    return item;
}

QSharedPointer<RemoteDeviceItem> Bluetooth::processRemoteDeviceInfo(const QBluetoothDeviceInfo &deviceInfo)
{
    if (!deviceInfo.isValid())
        return QSharedPointer<RemoteDeviceItem>(nullptr);

    QSharedPointer<RemoteDeviceItem> item(new RemoteDeviceItem);

    // Display text
    item->setDisplayText(deviceInfo.name() + "\n" + deviceInfo.address().toString());

    // Connection string
    item->setConnectionString(deviceInfo.address().toString());

    // Additional info
    QStringList additionalInfo;
    // RSSI
    additionalInfo << "RSSI:" << QString::number(deviceInfo.rssi());
    // UUIDs
    for(auto UUID: deviceInfo.serviceUuids())
        additionalInfo << "UUID:" << UUID.toString();

    item->setAdditionalInfo(additionalInfo);

    // If there is already a connection to this device
    if (!socket.isNull() && socket->state() == QBluetoothSocket::ConnectedState && socket->peerAddress() == deviceInfo.address())
    {
        item->setConnectionState(RemoteDeviceItem::CONNECTED);
    }

    return item;
}

void Bluetooth::onHostModeStateChanged(QBluetoothLocalDevice::HostMode mode)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << mode;
#endif
}

void Bluetooth::onSocketReadyRead()
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
#endif

    QByteArray rx = socket->readAll();
    qDebug() << qPrintable(rx);

    socket->write(rx);
}

void Bluetooth::onSocketStateChanged(QBluetoothSocket::SocketState state)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << state;
#endif

    //    switch (state) {
    //    case QBluetoothSocket::UnconnectedState:
    //    case QBluetoothSocket::ConnectedState:
    //    case QBluetoothSocket::ConnectingState:
    //    case QBluetoothSocket::ServiceLookupState:
    //    case QBluetoothSocket::BoundState:
    //    case QBluetoothSocket::ClosingState:
    //    case QBluetoothSocket::ListeningState:
    //    default:
    //        break;
    //    }
}

void Bluetooth::onSocketError(QBluetoothSocket::SocketError error)
{
#ifdef DEBUG_LOG
    qDebug() << endl << __PRETTY_FUNCTION__;
    qDebug() << error;
#endif
}
