#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "Bluetooth.h"
#include "Model.h"


class Communicator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Model* serialModel READ serialModel CONSTANT)
    Q_PROPERTY(Model* bluetoothModel READ bluetoothModel CONSTANT)
    Q_PROPERTY(CONNECTION_TYPE connectionType READ connectionType WRITE setConnectionType NOTIFY connectionTypeChanged);

public:
    explicit Communicator(QObject *parent = nullptr);
    void Ports();
    void send(const QByteArray& data);

    Model* serialModel() const;
    Model* bluetoothModel() const;

    enum CONNECTION_TYPE
    {
        BLUETOOTH,
        USB_UART,
        UNKNOWN
    };
    Q_ENUM(CONNECTION_TYPE)

    CONNECTION_TYPE connectionType() const;

private:
    Bluetooth *bt;
    QSerialPort port;
    QByteArray rx_buffer;

    // Available communication ports data model
    Model* serialModel_;
    Model* bluetoothModel_;
    CONNECTION_TYPE connectionType_ = UNKNOWN;

signals:
    void triggerSamples(QByteArray samples);
    void connectionTypeChanged(CONNECTION_TYPE connectionType);

public slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);
    void setConnectionType(CONNECTION_TYPE connectionType);
    void findDevices(CONNECTION_TYPE connectionType);

};

#endif // COMMUNICATOR_H
