#ifndef SERIAL_ITEM_H
#define SERIAL_ITEM_H

#include <QObject>


class SerialItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString manufacturer READ manufacturer WRITE setManufacturer NOTIFY manufacturerChanged)
    Q_PROPERTY(QString serialNumber READ serialNumber WRITE setSerialNumber NOTIFY serialNumberChanged)
    Q_PROPERTY(QString vendorId READ vendorId WRITE setVendorId NOTIFY vendorIdChanged)
    Q_PROPERTY(QString productId READ productId WRITE setProductId NOTIFY productIdChanged)

public:
    explicit SerialItem(QObject *parent = nullptr);

    QString name() const;
    QString location() const;
    QString description() const;
    QString manufacturer() const;
    QString serialNumber() const;
    QString vendorId() const;
    QString productId() const;

public slots:
    void setName(QString name);
    void setLocation(QString location);
    void setDescription(QString description);
    void setManufacturer(QString manufacturer);
    void setSerialNumber(QString serialNumber);
    void setVendorId(QString vendorId);
    void setProductId(QString productId);

private:
    QString name_;
    QString location_;
    QString description_;
    QString manufacturer_;
    QString serialNumber_;
    QString vendorId_;
    QString productId_;

signals:
    void nameChanged(QString name);
    void locationChanged(QString location);
    void descriptionChanged(QString description);
    void manufacturerChanged(QString manufacturer);
    void serialNumberChanged(QString serialNumber);
    void vendorIdChanged(QString vendorId);
    void productIdChanged(QString productId);
};

#endif // SERIAL_ITEM_H
