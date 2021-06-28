#include "HardwareManager.h"
#include "IOItem.h"
#include <QThread>
#include <QCoreApplication>

#define DEBUG_LOG
#ifdef DEBUG_LOG
  #include <QDebug>
#endif


HardwareManager::HardwareManager(QSharedPointer<CommunicationManager> communicationManager, QObject *parent)
    : QObject(parent)
    , _communicationManager(communicationManager)
{
    _variableOutputModel = new Model(this);
    _switchableInputModel = new Model(this);
    _switchableOutputModel = new Model(this);

    QObject::connect(communicationManager.data(), &CommunicationManager::received, this, &HardwareManager::onReceived);

    //initialize();


//    // Test values
//    // Variable outputs model

//    voModel_ = new Model(this);
//    {
//        QSharedPointer<IOItem> i (new IOItem);
//        i->setActive(true);
//        i->setDescription("IAT");
//        i->setAddress(255);
//        i->setSetValue(47);
//        i->setActualValue(47);
//        voModel_->insert(i);
//    }

//    {
//        QSharedPointer<IOItem> i (new IOItem);
//        i->setActive(true);
//        i->setDescription("WBO2");
//        i->setAddress(255);
//        i->setSetValue(85);
//        i->setActualValue(85);
//        voModel_->insert(i);
//    }
//    {
//        QSharedPointer<IOItem> i (new IOItem);
//        i->setActive(true);
//        i->setDescription("MAT");
//        i->setAddress(255);
//        i->setSetValue(51);
//        i->setActualValue(51);
//        voModel_->insert(i);
//    }

//    {
//        QSharedPointer<IOItem> i (new IOItem);
//        i->setActive(true);
//        i->setDescription("CLT");
//        i->setAddress(255);
//        i->setSetValue(101);
//        i->setActualValue(101);
//        voModel_->insert(i);
//    }

//    {
//        QSharedPointer<IOItem> i (new IOItem);
//        i->setActive(true);
//        i->setDescription("TPS");
//        i->setAddress(255);
//        i->setSetValue(18);
//        i->setActualValue(18);
//        voModel_->insert(i);
//    }


//    // Test values
//    // Switchable outputs model
//    {
//    soModel_ = new Model(this);

//    QSharedPointer<IOItem> so1(new IOItem);
//    so1->setActive(true);
//    so1->setDescription("Trigger 1");
//    so1->setAddress(255);
//    so1->setSetValue(1);
//    so1->setActualValue(1);

//    QSharedPointer<IOItem> so2(new IOItem);
//    so2->setActive(true);
//    so2->setDescription("Trigger 2");
//    so2->setAddress(255);
//    so2->setSetValue(0);
//    so2->setActualValue(0);

//    QSharedPointer<IOItem> so3(new IOItem);
//    so3->setActive(true);
//    so3->setDescription("Launch control");
//    so3->setAddress(255);
//    so3->setSetValue(0);
//    so3->setActualValue(0);

//    QSharedPointer<IOItem> so4(new IOItem);
//    so4->setActive(true);
//    so4->setDescription("Trigger 3");
//    so4->setAddress(255);
//    so4->setSetValue(0);
//    so4->setActualValue(0);

//    soModel_->insert(so1);
//    soModel_->insert(so2);
//    soModel_->insert(so3);
//    soModel_->insert(so4);
//    }

//    // Test values
//    // Switchable inputs model
//    {
//    siModel_ = new Model(this);

//    QSharedPointer<IOItem> si1(new IOItem);
//    si1->setActive(true);
//    si1->setDescription("Inj bank 1");
//    si1->setAddress(255);
//    si1->setSetValue(0);
//    si1->setActualValue(1);

//    QSharedPointer<IOItem> si2(new IOItem);
//    si2->setActive(true);
//    si2->setDescription("Launch control");
//    si2->setAddress(255);
//    si2->setSetValue(0);
//    si2->setActualValue(0);

//    QSharedPointer<IOItem> si3(new IOItem);
//    si3->setActive(true);
//    si3->setDescription("Test");
//    si3->setAddress(255);
//    si3->setSetValue(1);
//    si3->setActualValue(1);

//    QSharedPointer<IOItem> si4(new IOItem);
//    si4->setActive(true);
//    si4->setDescription("Warmup enrichment");
//    si4->setAddress(255);
//    si4->setSetValue(0);
//    si4->setActualValue(0);

//    siModel_->insert(si1);
//    siModel_->insert(si2);
//    siModel_->insert(si3);
//    siModel_->insert(si4);
    //    }
}

Model *HardwareManager::variableOutputModel() const
{
    return _variableOutputModel;
}

Model *HardwareManager::switchableOutputModel() const
{
    return _switchableOutputModel;
}

Model *HardwareManager::switchableInputModel() const
{
    return _switchableInputModel;

}

Model *HardwareManager::triggerPatternModel() const
{
    return _triggerPatternModel;
}

// TODO: Rename probably
// Received raw binary packet data
void HardwareManager::onReceived(QByteArray rawData)
{
#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
    if (!rawData.isEmpty())
    {
        uint8_t operation = rawData.at(0);
        uint8_t cmd = rawData.at(1);
        uint8_t index = rawData.at(2);

        rawData = rawData.remove(0,3);

        qDebug() << "Operation:" << QString("0x%1").arg(operation, 0, 16);
        qDebug() << "Cmd:" << QString("0x%1").arg(cmd, 0, 16);
        qDebug() << "Index:" << QString::number(index);
        qDebug() << QString(rawData) << Qt::endl;

    }
    //qDebug() << "ASCII:" << QString(rawData);
#endif

}
