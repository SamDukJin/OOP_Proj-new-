#include "featureswindow.h"
#include "depositwindow.h"
#include "ui_featureswindow.h"
#include "withdrawwindow.h"
#include "mainbankgui.h"

FeaturesWindow::FeaturesWindow(const QString &name, const QString &accountNum, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::FeaturesWindow), userName(name), accountNumber(accountNum), accountBalance(balance) {

    if (accountBalance < 0) accountBalance = 0;

    ui->setupUi(this);

    ui->UsernamLabel->setText("Username: "+ userName);
    ui->AccNumLabel->setText("Account Number: " + accountNumber);
    ui->BalanceLabel->setText("Balance: " + QString::number(accountBalance, 'f', 2) + " ฿");

    connect(ui->HomeBtn, &QPushButton::clicked, this, &FeaturesWindow::goHomeBtn);
    connect(ui->DepositBtn, &QPushButton::clicked, this, &FeaturesWindow::goDeposit);
    connect(ui->WithdrawBtn, &QPushButton::clicked, this, &FeaturesWindow::goWithdraw);
}

FeaturesWindow::~FeaturesWindow() {
    delete ui;
}

void FeaturesWindow::goHomeBtn() {
    this->hide();

    MainBankGUI *gotoMainBankWin = new MainBankGUI(userName, accountNumber, accountBalance);
    gotoMainBankWin->setModal(true);
    gotoMainBankWin->exec();

    delete gotoMainBankWin  ;
    this->close();
}

void FeaturesWindow::goDeposit() {
    this->hide();

    DepositWindow *depositWin = new DepositWindow(userName, accountNumber, accountBalance);
    depositWin->setModal(true);
    depositWin->exec();

    delete depositWin;
    this->close();
}

void FeaturesWindow::goWithdraw(){
    this->hide();

    WithdrawWindow *withdrawwin = new WithdrawWindow(userName, accountNumber, accountBalance);
    withdrawwin->setModal(true);
    withdrawwin->exec();

    delete withdrawwin;
    this->close();
}
