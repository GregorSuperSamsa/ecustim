#include "IO.h"
#include "Item.h"


IO::IO(QSharedPointer<Communicator> communicator, QObject *parent)
    : QObject(parent)
    , communicator(communicator)
{
    voModel_ = new Model(this);

    Item* i1 = new Item(this);
    i1->setActive(true);
    i1->setDescription("RPM");
    voModel_->insert(i1);

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
