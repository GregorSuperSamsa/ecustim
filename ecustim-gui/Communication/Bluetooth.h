#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>

class Bluetooth : public QObject
{
    Q_OBJECT
public:
    explicit Bluetooth(QObject *parent = nullptr);

signals:

};

#endif // BLUETOOTH_H
