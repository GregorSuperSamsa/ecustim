#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include "Communicator.h"
#include <QtCharts/QAbstractSeries>

namespace Ui {
class Test;
}

class Test : public QMainWindow
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr);
    ~Test();

private:
    Ui::Test *ui;
    //Communicator c;

public slots:
    void on_pushButton_pressed();

};

#endif // TEST_H
