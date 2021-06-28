#ifndef UART_H
#define UART_H

#include <QSerialPort>
#include <QTimer>
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

    // Start discovering currently available remote devices
    void startRemoteDeviceDiscovery();

    // Stop discovering currently available remote devices
    void stopRemoteDeviceDiscovery();

private:
    QScopedPointer<QSerialPort> localDevice;
    QTimer timer;

public slots:
    // Send raw data to the remote device
    void send(const QByteArray& bytes);

private slots:
    void onReadyRead();
    void onTimeout();
    void onError(QSerialPort::SerialPortError error);

};

#endif // UART_H
