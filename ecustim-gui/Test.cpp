#include "Test.h"
#include "ui_Test.h"
#include "Hardware/IOItem.h"
#include "Communication/Protocol.h"
#include "Communication/ProtocolHandler.h"
#include "QThread"


Test::Test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);
    hide();

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

void Test::setProtocolHandler(QSharedPointer<ProtocolHandler> protocolHandler)
{
    this->protocolHandler = protocolHandler;
}

void Test::setCommunicator(QSharedPointer<CommunicationManager> communicator)
{
    this->communicator = communicator;

}

void Test::setHardwareManager(QSharedPointer<HardwareManager> hardwareManager)
{
    this->hardwareManager = hardwareManager;
}

void Test::on_pushButton_pressed()
{
    //namespace FrameByte
    // Acknowledge
    static const uint8_t ACK = 0x06;
    // Negative acknowledge
    static const uint8_t NAK = 0x15;
    // Start of text (packet)
    static const uint8_t STX = 0xAF;
    // End of text (packet)IOf
    static const uint8_t ETX = 0xAB;
    // Data link escape
    static const uint8_t DLE = 0xAC;

    //namespace Operation
    static const uint8_t READ = 0xAD;
    static const uint8_t WRITE = 0xAE;

    //namespace Command
    // Trigger Pattern Commands
    static const uint8_t TRIGGER_PATTERN_CMD_MASK = 0xA0;
    static const uint8_t TRIGGER_PATTERN_INDEX    = 0xA1;
    static const uint8_t TRIGGER_PATTERN_NAME     = 0xA2;
    static const uint8_t TRIGGER_PATTERN_DATA     = 0xA3;
    static const uint8_t TRIGGER_PATTERN_DEGREES  = 0xA4;
    static const uint8_t TRIGGER_PATTERN_ROTATION = 0xA5;
    static const uint8_t TRIGGER_PATTERN_RPM      = 0xA6;
    static const uint8_t TRIGGER_PATTERN_COUNT    = 0xA7;
    static const uint8_t TRIGGER_PATTERN_ENABLE   = 0xA8;

    QByteArray data;
    for (int i = 0; i < 53; i++)
    {
        data.append(READ);
        data.append(TRIGGER_PATTERN_NAME);
        data.append((uint8_t)i);

        communicator->send(data);
        data.clear();
    }

//    for (int j = 0; j < 20; j++)
//    {
//        QCoreApplication::processEvents();
//        QThread::msleep(10);
//    }
}

void Test::onTimeout()
{
    for (int i = 0; i < hardwareManager->switchableInputModel()->count(); ++i)
    {
        QSharedPointer<IOItem> item = qobject_cast<QSharedPointer<IOItem>>(hardwareManager->switchableInputModel()->data(i));
        if (!item.isNull())
        {
            if (item->value() == 0)
                item->setValue(1);
            else
                item->setValue(0);
        }
    }


 //   io->siModel()->

}
