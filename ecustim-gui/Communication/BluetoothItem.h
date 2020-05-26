#ifndef BLUETOOTH_ITEM_H
#define BLUETOOTH_ITEM_H

#include <QObject>


class BluetoothItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString rssi READ rssi WRITE setRssi NOTIFY rssiChanged)

public:
    explicit BluetoothItem(QObject *parent = nullptr);

    QString name() const;
    QString address() const;
    QString rssi() const;

public slots:
    void setName(QString name);
    void setAddress(QString address);
    void setRssi(QString rssi);

private:
    QString name_;
    QString address_;
    QString rssi_;

signals:
    void nameChanged(QString name);
    void addressChanged(QString address);
    void rssiChanged(QString rssi);

};

#endif // BLUETOOTH_ITEM_H
