#ifndef UART_H
#define UART_H

#include <QSerialPort>
#include "Communication/Communication.h"
#include "Communication/RemoteDeviceItem.h"


class Uart : public Communication
{
    Q_OBJECT

public:
    explicit Uart(QObject *parent = nullptr);

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

    // Get currently available remote devices
    void getRemoteDevices();

    // Send raw data to the remote device
    void send(const QByteArray& bytes);

private:
    QScopedPointer<QSerialPort> localDevice;

};

#endif // UART_H
