#include "IOManager.h"
#include "IOItem.h"


IO::IO(QSharedPointer<CommunicationManager> communicator, QObject *parent)
    : QObject(parent)
    , communicator(communicator)
{
    // Test values
    // Variable outputs model
    {
    voModel_ = new Model(this);

    QSharedPointer<Item> i1(new Item);
    i1->setActive(true);
    i1->setDescription("RPM");
    i1->setAddress(255);
    i1->setSetValue(0);
    i1->setActualValue(0);
    voModel_->insert(i1);
    //
    QSharedPointer<Item> i3(new Item);
    i3->setActive(true);
    i3->setDescription("TPS");
    i3->setAddress(255);
    i3->setSetValue(0);
    i3->setActualValue(0);
    voModel_->insert(i3);
    //
    QSharedPointer<Item> i2(new Item);
    i2->setActive(true);
    i2->setDescription("CLT");
    i2->setAddress(255);
    i2->setSetValue(0);
    i2->setActualValue(0);
    voModel_->insert(i2);
    }

    // Test values
    // Switchable outputs model
    {
    soModel_ = new Model(this);

    QSharedPointer<Item> so1(new Item);
    so1->setActive(true);
    so1->setDescription("Trigger 1");
    so1->setAddress(255);
    so1->setSetValue(0);
    so1->setActualValue(0);

    QSharedPointer<Item> so2(new Item);
    so2->setActive(true);
    so2->setDescription("Trigger 2");
    so2->setAddress(255);
    so2->setSetValue(0);
    so2->setActualValue(0);

    QSharedPointer<Item> so3(new Item);
    so3->setActive(true);
    so3->setDescription("Launch control");
    so3->setAddress(255);
    so3->setSetValue(0);
    so3->setActualValue(0);

    QSharedPointer<Item> so4(new Item);
    so4->setActive(true);
    so4->setDescription("Trigger 3");
    so4->setAddress(255);
    so4->setSetValue(0);
    so4->setActualValue(0);

    soModel_->insert(so1);
    soModel_->insert(so2);
    soModel_->insert(so3);
    soModel_->insert(so4);
    }

    // Test values
    // Switchable inputs model
    {
    siModel_ = new Model(this);

    QSharedPointer<Item> si1(new Item);
    si1->setActive(true);
    si1->setDescription("Injector 1");
    si1->setAddress(255);
    si1->setSetValue(0);
    si1->setActualValue(1);

    QSharedPointer<Item> si2(new Item);
    si2->setActive(true);
    si2->setDescription("Launch control in");
    si2->setAddress(255);
    si2->setSetValue(0);
    si2->setActualValue(0);

    QSharedPointer<Item> si3(new Item);
    si3->setActive(true);
    si3->setDescription("Test input 666");
    si3->setAddress(255);
    si3->setSetValue(0);
    si3->setActualValue(1);

    QSharedPointer<Item> si4(new Item);
    si4->setActive(true);
    si4->setDescription("Warmup enrichment");
    si4->setAddress(255);
    si4->setSetValue(0);
    si4->setActualValue(0);

    siModel_->insert(si1);
    siModel_->insert(si2);
    siModel_->insert(si3);
    siModel_->insert(si4);
    }
}

Model* IO::voModel() const
{
    return voModel_;
}

Model* IO::soModel() const
{
    return soModel_;
}

Model* IO::siModel() const
{
    return siModel_;
}
