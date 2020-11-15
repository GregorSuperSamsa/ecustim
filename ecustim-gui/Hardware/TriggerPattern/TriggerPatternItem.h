#ifndef TRRIGER_PATTERN_ITEM_H
#define TRRIGER_PATTERN_ITEM_H

#include <QObject>
#include <QDebug>
#include <QVector>


class TriggerPatternItem: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QVector<int> data READ data WRITE setData NOTIFY dataChanged);

public:
    TriggerPatternItem(QObject *parent = nullptr);

    QString name() const;
    QVector<int> data() const;

private:
    QString name_;
    QVector<int> data_;

public slots:
    void setName(QString name);
    void setData(QVector<int> data);

signals:
    void nameChanged(QString name);
    void dataChanged(QVector<int> data);

};

#endif // TRRIGER_PATTERN_ITEM_H
