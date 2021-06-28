#ifndef COMMUNICATHardwareManagerN_H
#define COMMUNICATHardwareManagerN_H

#include <QObject>
#include <QQueue>
#include "Protocol.h"
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

    // Start discovering currently available remote devices
    virtual void startRemoteDeviceDiscovery() = 0;

    // Stop discovering currently available remote devices
    virtual void stopRemoteDeviceDiscovery() = 0;


public slots:
    // Send raw data
    virtual void send(const QByteArray& bytes) = 0;

signals:
    // Raw data received
    void received(QByteArray bytes);

    // Discovery state
    void remoteDeviceDiscovered(QSharedPointer<RemoteDeviceItem>);
    void remoteDeviceDiscoveryFinished();
    // Connection state
    void remoteDeviceConnected(QString connectionInfo);
    void remoteDeviceDisconnected(QString connectionInfo);



};

#endif // COMMUNICATHardwareManagerN_H
