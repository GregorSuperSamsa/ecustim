#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include <QtCharts/QAbstractSeries>
#include <QTimer>
#include "Communication/CommunicationManager.h"
#include "Hardware/IO/IOManager.h"


namespace Ui {
class Test;
}

class Test : public QMainWindow
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr);
    ~Test();

    void setCommunicator(QSharedPointer<CommunicationManager> communicator);
    void setIO(QSharedPointer<IO> io);

private:
    Ui::Test *ui;
    QSharedPointer<CommunicationManager> communicator;
    QSharedPointer<IO> io;
    QTimer* timer;

public slots:
    void on_pushButton_pressed();
    void onTimeout();
};

#endif // TEST_H
