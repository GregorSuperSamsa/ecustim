#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <Communication/RemoteDeviceItem.h>

class Communication : public QObject
{
    Q_OBJECT
public:
    explicit Communication(QObject *parent = nullptr);

    // Initialize the communication interface
    virtual void initialize() = 0;

    // Check whether the communication interface is valid on this host
    virtual bool isValid() const = 0;

    // Connect to a selected remote device
    virtual void connect(const QString& connectionInfo) = 0;

    // Disconnect from remote device
    virtual void disconnect() = 0;

    // Check whether we are currently connected to a remote device
    virtual bool isConnected() const = 0;

    // Get currently available remote devices
    virtual void getRemoteDevices() = 0;

    // Send raw data to the remote device
    virtual void send(const QByteArray& bytes) = 0;

signals:
    void remoteDeviceDiscovered(QSharedPointer<RemoteDeviceItem>);
    void remoteDeviceDiscoveryFinished();
    void connectionStatus(bool isConnected);

};

#endif // COMMUNICATION_H
