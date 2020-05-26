#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include "BluetoothItem.h"

class Bluetooth : public QObject
{
    Q_OBJECT
public:
    explicit Bluetooth(QObject *parent = nullptr);



private:
    QBluetoothDeviceDiscoveryAgent* agent;
    QList<QBluetoothAddress> remoteDevices;
    QBluetoothLocalDevice* device;
    QString name;

public slots:
    void onDeviceDiscovered(const QBluetoothDeviceInfo &device);
    void onDeviceDiscoveryFinished();

signals:
    //void deviceDiscovered(BluetoothItem item);


signals:

};

#endif // BLUETOOTH_H
