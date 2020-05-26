#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include "Communication/Communicator.h"
#include "IO/IO.h"
#include <QtCharts/QAbstractSeries>
#include <QTimer>


namespace Ui {
class Test;
}

class Test : public QMainWindow
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr);
    ~Test();

    void setCommunicator(QSharedPointer<Communicator> communicator);
    void setIO(QSharedPointer<IO> io);

private:
    Ui::Test *ui;
    QSharedPointer<Communicator> communicator;
    QSharedPointer<IO> io;
    QTimer* timer;

public slots:
    void on_pushButton_pressed();
    void onTimeout();
};

#endif // TEST_H
