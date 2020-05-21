#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(QObject *parent = nullptr);
    void Ports();
    void send(const QByteArray& data);

private:
    QSerialPort port;
    QByteArray rx_buffer;

signals:
    void triggerSamples(QByteArray samples);

public slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);
};

#endif // COMMUNICATOR_H
