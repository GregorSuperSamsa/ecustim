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
    return mItems.size();
}

QVariant Model::data(const QModelIndex& index, int role) const
{

    Q_UNUSED(role)

    QObject* item = mItems.at(index.row());
    return QVariant::fromValue(item);
}

void Model::insert(QObject* item)
{
    beginInsertRows(QModelIndex(), 0, 0);
    mItems.push_front(item);
    endInsertRows();

    emit countChanged(count());
}

void Model::remove(QObject* item)
{
    for (int i = 0; i < mItems.size(); ++i)
    {
        if (mItems.at(i) == item)
        {
            beginRemoveRows(QModelIndex(), i, i);
            mItems.remove(i);
            endRemoveRows();

            emit countChanged(count());
            break;
        }
    }
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "item";

    return roles;
}
