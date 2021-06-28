#ifndef HARDWARE_ITEM_H
#define HARDWARE_ITEM_H

#include <QObject>
#include <QDebug>


class HardwareItem: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int     value       READ value       WRITE setValue       NOTIFY valueChanged)
    Q_PROPERTY(bool    active      READ active      WRITE setActive      NOTIFY activeChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    HardwareItem(QObject *parent = nullptr);

    void setValue(int value);
    int value() const;

    void setActive(bool active);
    bool active() const;

    void setDescription(QString description);
    QString description() const;

private:
    int _value;
    bool _active;
    QString _description;

signals:
    void valueChanged(int value);
    void activeChanged(bool active);
    void descriptionChanged(QString description);
};

#endif // HARDWARE_ITEM_H
