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

public:
    explicit Communicator(QObject *parent = nullptr);
    void Ports();
    void send(const QByteArray& data);

    Model* serialModel() const;
    Model* bluetoothModel() const;

private:
    Bluetooth *bt;
    QSerialPort port;
    QByteArray rx_buffer;

    // Available communication ports data model
    Model* serialModel_;
    Model* bluetoothModel_;

signals:
    void triggerSamples(QByteArray samples);

public slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);
};

#endif // COMMUNICATOR_H
