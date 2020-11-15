#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QDebug>


class IOItem: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int setValue READ setValue WRITE setSetValue NOTIFY setValueChanged)
    Q_PROPERTY(int actualValue READ actualValue WRITE setActualValue NOTIFY actualValueChanged)
    Q_PROPERTY(int address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    IOItem(QObject *parent = nullptr);
    //
    int setValue() const;
    void setSetValue(int setValue);
    //
    int actualValue() const;
    void setActualValue(int actualValue);
    //
    int address() const;
    void setAddress(int address);
    //
    bool active() const;
    void setActive(bool active);
    //
    QString description() const;
    void setDescription(QString description);

private:
    int setValue_;
    int actualValue_;
    int address_;
    bool active_;
    QString description_;

signals:
    void setValueChanged(int setValue);
    void actualValueChanged(int actualValue);
    void addressChanged(int address);
    void activeChanged(bool active);
    void descriptionChanged(QString description);
};

#endif // ITEM_H
