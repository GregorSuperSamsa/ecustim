#ifndef HARDWARE_MANAGER_H
#define HARDWARE_MANAGER_H

#include <QObject>
#include <QSharedPointer>
#include "Communication/CommunicationManager.h"
#include "UI/Model.h"


class HardwareManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Model* variableOutputModel   READ variableOutputModel   CONSTANT)
    Q_PROPERTY(Model* switchableOutputModel READ switchableOutputModel CONSTANT)
    Q_PROPERTY(Model* switchableInputModel  READ switchableInputModel  CONSTANT)
    Q_PROPERTY(Model* triggerPatternModel   READ triggerPatternModel   CONSTANT)

public:
    explicit HardwareManager(QSharedPointer<CommunicationManager> communicationManager, QObject *parent = nullptr);

    Model* variableOutputModel() const;
    Model* switchableOutputModel() const;
    Model* switchableInputModel() const;
    Model* triggerPatternModel() const;

private:
    // Variable outputs data model
    Model* _variableOutputModel;
    // Switchable outputs data model
    Model* _switchableOutputModel;
    // Switchable inputs data model
    Model* _switchableInputModel;
    // Trigger patterns data model
    Model* _triggerPatternModel;
    // Communicator
    QSharedPointer<CommunicationManager> _communicationManager;

private slots:
    void onReceived(QByteArray rawData);

};

#endif // HARDWARE_MANAGER_H
