#include "featureswindow.h"
#include "ui_featureswindow.h"

#include "utils.h"
#include "mainbankgui.h"
#include "depositwindow.h"
#include "withdrawwindow.h"
#include "transferwindow.h"

FeaturesWindow::FeaturesWindow(const QString &name, const QString &accountNum, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::FeaturesWindow), userName(name), accountNumber(accountNum), accountBalance(balance) {

    if (accountBalance < 0) accountBalance = 0;
    ui->setupUi(this);

    ui->UsernamLabel->setText("Username: "+ userName);
    ui->AccNumLabel->setText("Account Number: " + accountNumber);
    ui->BalanceLabel->setText("Balance: " + formatBalance(accountBalance));

    connect(ui->HomeBtn, &QPushButton::clicked, this, &FeaturesWindow::goHomeBtn);
    connect(ui->DepositBtn, &QPushButton::clicked, this, &FeaturesWindow::goDeposit);
    connect(ui->WithdrawBtn, &QPushButton::clicked, this, &FeaturesWindow::goWithdraw);
    connect(ui->TransBtn, &QPushButton::clicked, this, &FeaturesWindow::goTransfer);
}

FeaturesWindow::~FeaturesWindow() {
    delete ui;
}

void FeaturesWindow::goHomeBtn() {
    this->hide();

    MainBankGUI *gotoMainBankWin = new MainBankGUI(userName, accountNumber, accountBalance,this);
    gotoMainBankWin->setModal(true);
    gotoMainBankWin->exec();
    delete gotoMainBankWin;
}

void FeaturesWindow::goDeposit() {
    this->hide();

    DepositWindow *depositWin = new DepositWindow(userName, accountNumber, accountBalance,this);
    depositWin->setModal(true);
    depositWin->exec();
    delete depositWin;
}

void FeaturesWindow::goWithdraw(){
    this->hide();

    WithdrawWindow *withdrawwin = new WithdrawWindow(userName, accountNumber, accountBalance,this);
    withdrawwin->setModal(true);
    withdrawwin->exec();
    delete withdrawwin;
}
void FeaturesWindow::goTransfer(){
    this->hide();
    transferwindow *transferwin = new transferwindow(userName, accountNumber, accountBalance,this);
    transferwin->setModal(true);
    transferwin->exec();
    delete transferwin;
}
