#include "Communicator.h"
#include <QtDebug>

Communicator::Communicator(QObject *parent) : QObject(parent)
{
    QObject::connect(&port, &QSerialPort::readyRead, this, &Communicator::handleReadyRead);
    QObject::connect(&port, &QSerialPort::errorOccurred, this, &Communicator::handleError);
}

void Communicator::send(const QByteArray& data)
{
    if (port.isOpen())
    {
        port.write(data);
        //port->flush();
    }
    else
        qDebug() << "Port not open!";
}

void Communicator::Ports()
{
    QString port_name;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        port_name = info.portName();
        QString s = QObject::tr("Port: ") + info.portName() + "\n"
                + QObject::tr("Location: ") + info.systemLocation() + "\n"
                + QObject::tr("Description: ") + info.description() + "\n"
                + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
                + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
                + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
                + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";
        qDebug() << qPrintable(s);
    }

    port.setPortName(port_name);
    port.setBaudRate(QSerialPort::Baud9600);
    port.setFlowControl(QSerialPort::NoFlowControl);
    port.setParity(QSerialPort::NoParity);
    port.setDataBits(QSerialPort::Data8);
    port.setStopBits(QSerialPort::OneStop);
    port.open(QIODevice::ReadWrite);

}

void Communicator::handleReadyRead()
{
    rx_buffer.append(port.readAll());

    QList<QByteArray> list = rx_buffer.split('\n');
    rx_buffer.clear();
    if (!list.last().contains('\n'))
    {
        rx_buffer.append(list.last());
        list.removeLast();
    }


//    QByteArray test;
//    test[0] = 0;
//    test[1] = 3;
//    test[2] = 0;
//    test[3] = 3;
//    test[4] = 0;
//    test[5] = 3;
//    test[6] = 0;
//    test[7] = 3;
//    test[8] = 0;
//    test[9] = 3;
//    test[10] = 0;
//    list.clear();
//    list.append(test);






    if (list.size() > 0)
    {
        emit triggerSamples(list.at(0));
    }

    for(auto b : list)
    {
        qDebug() << b;
        //qDebug() << qPrintable(QString::fromUtf8(b));
    }
}

void Communicator::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ReadError)
    {
        qDebug() << qPrintable(port.portName());
        qDebug() << qPrintable(port.errorString());
    }
}
