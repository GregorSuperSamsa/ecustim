#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>


class Model : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count CONSTANT)

public:
    Model(QObject *parent = nullptr);

    int rowCount(const QModelIndex&) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QSharedPointer<QObject> data(int index) const;

    int count() const;

public slots:
    void insert(QSharedPointer<QObject> item);
    void remove(QSharedPointer<QObject> item);
    void clearAll();

signals:
    void countChanged(int count);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<QSharedPointer<QObject>> items;
    int count_;
};
#endif // MODEL_H
