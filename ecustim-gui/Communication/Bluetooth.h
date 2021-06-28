#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothSocket>
#include "Communication/Communication.h"
#include "Communication/RemoteDeviceItem.h"


class Bluetooth : public Communication
{
    Q_OBJECT

public:
    explicit Bluetooth(QObject *parent = nullptr);
    virtual ~Bluetooth();

    // Initialize the communication interface
    void initialize();

    // Check whether the communication interface is valid on this host
    bool isValid() const;

    // Connect to a selected remote device
    void connect(const QString& connectionInfo);

    // Disconnect from remote device
    void disconnect();

    // Check whether we are currently connected to a remote device
    bool isConnected() const;

    // Start discovering currently available remote devices
    void startRemoteDeviceDiscovery();

    // Stop discovering currently available remote devices
    void stopRemoteDeviceDiscovery();

private:
    enum DISCOVERY_TYPE
    {
        DISCOVERY_TYPE_DEVICE,
        DISCOVERY_TYPE_SERVICE
    };
    static const DISCOVERY_TYPE discoveryType;

    void initializeRemoteDeviceDiscovery();

    QSharedPointer<RemoteDeviceItem> processRemoteDeviceInfo(const QBluetoothServiceInfo& serviceInfo);
    QSharedPointer<RemoteDeviceItem> processRemoteDeviceInfo(const QBluetoothDeviceInfo& deviceInfo);

    QScopedPointer<QBluetoothLocalDevice> localDevice;
    QScopedPointer<QBluetoothDeviceDiscoveryAgent> deviceAgent;
    QScopedPointer<QBluetoothServiceDiscoveryAgent> serviceAgent;
    QScopedPointer<QBluetoothSocket> socket;

public slots:
    // Send raw data to the remote device
    void send(const QByteArray& bytes);

private slots:
    //
    void onServiceDiscovered(const QBluetoothServiceInfo &info);
    void onServiceDiscoveryFinished();
    //
    void onDeviceDiscovered(const QBluetoothDeviceInfo& info);
    void onDeviceDiscoveryFinished();
    //
    void onDeviceConnected(QBluetoothAddress address);
    void onDeviceDisconnected(QBluetoothAddress address);
    //
    void onHostModeStateChanged(QBluetoothLocalDevice::HostMode);
    //
    void onSocketReadyRead();
    void onSocketStateChanged(QBluetoothSocket::SocketState state);
    void onSocketError(QBluetoothSocket::SocketError);
};

#endif // BLUETOOTH_H
