#include "Uart.h"
#include <QSerialPortInfo>
#include <QDebug>

//#define DEBUG_LOG


Uart::Uart(QObject *parent) : Communication(parent),
    localDevice(new QSerialPort(this))
{
}

// Initialize the communication interface
void Uart::initialize()
{
    if (isValid())
    {
        disconnect();

        // Set default settings
        localDevice->setBaudRate(QSerialPort::Baud115200);
        localDevice->setDataBits(QSerialPort::Data8);
        localDevice->setParity(QSerialPort::NoParity);
        localDevice->setStopBits(QSerialPort::OneStop);
        localDevice->setFlowControl(QSerialPort::NoFlowControl);

        // Problems with QSerialPort::readyRead signal not always emitted
        QObject::connect(localDevice.data(), &QSerialPort::readyRead, this, &Uart::onReadyRead);
        QObject::connect(localDevice.data(), &QSerialPort::errorOccurred, this, &Uart::onError);

        QObject::connect(&timer, &QTimer::timeout, this, &Uart::onTimeout);
        timer.setInterval(20);
        //timer.start();
    }
}

// Check whether the communication interface is valid on this host
bool Uart::isValid() const
{
    return !localDevice.isNull();
}

// Connect to a selected remote device
void Uart::connect(const QString& connectionInfo)
{
    if (connectionInfo.isEmpty())
        return;

    if (isValid())
    {
#ifdef DEBUG_LOG
        qDebug() << Qt::endl << __PRETTY_FUNCTION__;
        qDebug() << "Port:" << qPrintable(connectionInfo);
#endif
        disconnect();


        localDevice->setPortName(connectionInfo);
        if (localDevice->open(QIODevice::ReadWrite)) {
            emit remoteDeviceConnected(connectionInfo);
        }
    }
}

// Disconnect from remote device
void Uart::disconnect()
{
    if (isConnected()) {
        localDevice->close();
    }
    emit remoteDeviceDisconnected(localDevice->portName());
}

// Check whether we are currently connected to a remote device
bool Uart::isConnected() const
{
    return (isValid() && localDevice->isOpen());
}

// Start discovering currently available remote devices
void Uart::startRemoteDeviceDiscovery()
{
    if (isValid())
    {
        //
        QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
        for(const QSerialPortInfo& info : infos)
        {
            qDebug() << "Name:         " <<  qPrintable(info.portName());
            qDebug() << "Description:  " <<  qPrintable(info.description());
            qDebug() << "Vendor id:    " << (info.hasVendorIdentifier() ? qPrintable(QString::number(info.vendorIdentifier(), 16)) : qPrintable("NONE"));
            qDebug() << "Product id:   " << (info.hasProductIdentifier() ? qPrintable(QString::number(info.productIdentifier(), 16)) : qPrintable("NONE"));
            qDebug() << "Serial number:" <<  qPrintable(info.serialNumber());
            qDebug() << "Manufacturer: " <<  qPrintable(info.manufacturer());

            QSharedPointer<RemoteDeviceItem> item(new RemoteDeviceItem);
            //
            item->setDisplayText(info.description() + "\n" + info.portName());
            //
            item->setConnectionString(info.portName());
            // Additional info
            QStringList additionalInfo;
            QString field;
            // Vendor id
            if (info.hasVendorIdentifier())
            {
                field = QString::number(info.vendorIdentifier(), 16);
                if (!field.isEmpty()) {
                    additionalInfo << "Vendor identifier:" << field;
                }
            }
            // Product id
            if (info.hasProductIdentifier())
            {
                field = QString::number(info.productIdentifier(), 16);
                if (!field.isEmpty()) {
                    additionalInfo << "Product identifier:" << field;
                }
            }
            // Serial number
            field = info.serialNumber().trimmed();
            if (!field.isEmpty()) {
                additionalInfo << "Serial number:" << field;
            }
            // Manufacturer
            field = info.manufacturer().trimmed();
            if (!field.isEmpty()) {
                additionalInfo << "Manufacturer:" << field;
            }

            item->setAdditionalInfo(additionalInfo);

            emit remoteDeviceDiscovered(item);
        }
    }

    emit remoteDeviceDiscoveryFinished();
}

// Stop discovering currently available remote devices
void Uart::stopRemoteDeviceDiscovery()
{
    return;
}

// Send raw data to the remote device
void Uart::send(const QByteArray& bytes)
{
//#ifdef DEBUG_LOG
//    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
//    qDebug() << "ASCII:" << bytes;
//    qDebug() << "HEX:  " << bytes.toHex();
//#endif

    if (isConnected())
    {
        localDevice->write(bytes);
        //localDevice->flush();
    }
}

void Uart::onReadyRead()
{
    if ( !isConnected()) return;

    QByteArray bytes = localDevice->readAll();

    if (bytes.isEmpty()) return;

    emit received(bytes);

#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
    qDebug() << qPrintable(bytes);
    //qDebug() << "ASCII:" << bytes;
    //qDebug() << "HEX:  " << bytes.toHex();
#endif
}

void Uart::onTimeout()
{
    onReadyRead();
}

void Uart::onError(QSerialPort::SerialPortError error)
{
#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
    qDebug() << error;
#endif
    Q_UNUSED(error);
}
