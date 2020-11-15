#include "TriggerPatternItem.h"


TriggerPatternItem::TriggerPatternItem(QObject *parent):QObject(parent)
{
}

void TriggerPatternItem::setName(QString name)
{
    if (name_ == name)
        return;

    name_ = name;
    emit nameChanged(name_);
}

QString TriggerPatternItem::name() const
{
    return name_;
}

void TriggerPatternItem::setData(QVector<int> data)
{
    if (data_ == data)
        return;

    data_ = data;
    emit dataChanged(data_);
}

QVector<int> TriggerPatternItem::data() const
{
    return data_;
}
