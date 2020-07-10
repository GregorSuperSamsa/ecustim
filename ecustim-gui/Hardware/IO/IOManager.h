#ifndef IO_H
#define IO_H

#include <QObject>
#include <QSharedPointer>
#include "Communication/CommunicationManager.h"
#include "UI/Model.h"


class IO : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Model* voModel READ voModel CONSTANT)
    Q_PROPERTY(Model* soModel READ soModel CONSTANT)
    Q_PROPERTY(Model* siModel READ siModel CONSTANT)

public:
    explicit IO(QSharedPointer<CommunicationManager> communicator, QObject *parent = nullptr);

    Model* voModel() const;
    Model* soModel() const;
    Model* siModel() const;

private:
    // Variable outputs data model
    Model* voModel_;
    // Switchable outputs data model
    Model* soModel_;
    // Switchable inputs data model
    Model* siModel_;
    // Communicator
    QSharedPointer<CommunicationManager> communicator;

};

#endif // IO_H
