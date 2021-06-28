#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include <QtCharts/QAbstractSeries>
#include <QTimer>
#include "Communication/CommunicationManager.h"
#include "Communication/ProtocolHandler.h"
#include "Hardware/HardwareManager.h"


namespace Ui {
class Test;
}

class Test : public QMainWindow
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr);
    ~Test();

    void setProtocolHandler(QSharedPointer<ProtocolHandler> protocolHandler);
    void setCommunicator(QSharedPointer<CommunicationManager> communicator);
    void setHardwareManager(QSharedPointer<HardwareManager> hardwareManager);

private:
    Ui::Test *ui;
    QSharedPointer<ProtocolHandler> protocolHandler;
    QSharedPointer<CommunicationManager> communicator;
    QSharedPointer<HardwareManager> hardwareManager;
    QTimer* timer;

public slots:
    void on_pushButton_pressed();
    void onTimeout();
};

#endif // TEST_H
