#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>


class Model : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count CONSTANT)

public:
    Model(QObject *parent = nullptr);

    int rowCount(const QModelIndex&) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QObject* data(int index) const;

    int count() const;

public slots:
    void insert(QObject* item);
    void remove(QObject* item);
    void clearAll();

signals:
    void countChanged(int count);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<QObject*> mItems;
    int count_;
};
#endif // MODEL_H
