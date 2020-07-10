#include "Test.h"
#include "ui_Test.h"
#include "Hardware/IO/IOItem.h"


Test::Test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->setInterval(500);
    timer->start();

    QObject::connect(ui->lineEdit, &QLineEdit::returnPressed, ui->pushButton, &QPushButton::pressed);
}

Test::~Test()
{
    delete ui;
}

void Test::setCommunicator(QSharedPointer<CommunicationManager> communicator)
{
    this->communicator = communicator;

}

void Test::setIO(QSharedPointer<IO> io)
{
    this->io = io;
}

void Test::on_pushButton_pressed()
{
    QByteArray data = ui->lineEdit->text().toUtf8();
    data.append('\n');

    communicator->send(data);
}

void Test::onTimeout()
{
    for (int i = 0; i < io->siModel()->count(); ++i)
    {
        QSharedPointer<Item> item = qobject_cast<QSharedPointer<Item>>(io->siModel()->data(i));
        if (!item.isNull())
        {
            if (item->actualValue() == 0)
                item->setActualValue(1);
            else
                item->setActualValue(0);
        }
    }


 //   io->siModel()->

}
