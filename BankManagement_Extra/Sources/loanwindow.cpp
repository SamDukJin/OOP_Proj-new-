#include "loanwindow.h"
#include "ui_loanwindow.h"

LoanWindow::LoanWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoanWindow)
{
    ui->setupUi(this);
}

LoanWindow::~LoanWindow()
{
    delete ui;
}

