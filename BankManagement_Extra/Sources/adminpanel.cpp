#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "mainwindow.h"

adminpanel::adminpanel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::adminpanel)
{
    ui->setupUi(this);
}

adminpanel::~adminpanel()
{
    delete ui;
}

void adminpanel::homebtn(){
    qDebug() << "Hello! I need implementation!";
}
