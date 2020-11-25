#include "Model.h"


Model::Model(QObject *parent) : QAbstractListModel(parent)
{
}

int Model::count() const
{
    return rowCount(QModelIndex());
}

int Model::rowCount(const QModelIndex&) const
{
    return items.size();
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role)

    return QVariant::fromValue(items.at(index.row()).data());
}

QSharedPointer<QObject> Model::data(int index) const
{
    QSharedPointer<QObject> item(nullptr);
    if (index >= 0 && index < items.count())
    {
        item = items.at(index);
    }

    return item;
}

void Model::insert(QSharedPointer<QObject> item)
{
    beginInsertRows(QModelIndex(), 0, 0);
    items.push_back(item);
    endInsertRows();

    emit countChanged(count());
}

void Model::remove(QSharedPointer<QObject> item)
{
    for (int i = 0; i < items.size(); ++i)
    {
        if (items.at(i) == item)
        {
            beginRemoveRows(QModelIndex(), i, i);
            items.remove(i);
            endRemoveRows();

            emit countChanged(count());
            break;
        }
    }
}

void Model::clearAll()
{
    beginResetModel();
    items.clear();
    endResetModel();
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "item";

    return roles;
}
