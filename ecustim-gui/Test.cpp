#include "Test.h"
#include "ui_Test.h"

Test::Test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);

    //c.Ports();


    QObject::connect(ui->lineEdit, &QLineEdit::returnPressed, ui->pushButton, &QPushButton::pressed);
}

Test::~Test()
{
    delete ui;
}

void Test::on_pushButton_pressed()
{
    QByteArray data = ui->lineEdit->text().toUtf8();
    data.append('\n');
    //c.send(data);
}
