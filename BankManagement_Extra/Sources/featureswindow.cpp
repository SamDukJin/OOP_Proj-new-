#include "featureswindow.h"
#include "depositwindow.h"
#include "qsqlquery.h"
#include "ui_featureswindow.h"
#include "withdrawwindow.h"
#include "transferwindow.h"
#include "mainbankgui.h"
#include "databasemanager.h"

FeaturesWindow::FeaturesWindow(const QString &name, const QString &accountNum, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::FeaturesWindow), userName(name), accountNumber(accountNum), accountBalance(balance) {

    if (accountBalance < 0) accountBalance = 0;

    ui->setupUi(this);

    checkLoanStatus();

    ui->UsernamLabel->setText("Username: "+ userName);
    ui->AccNumLabel->setText("Account Number: " + accountNumber);
    ui->BalanceLabel->setText("Balance: " + QString::number(accountBalance, 'f', 2) + " ฿");

    connect(ui->HomeBtn, &QPushButton::clicked, this, &FeaturesWindow::goHomeBtn);
    connect(ui->DepositBtn, &QPushButton::clicked, this, &FeaturesWindow::goDeposit);
    connect(ui->WithdrawBtn, &QPushButton::clicked, this, &FeaturesWindow::goWithdraw);
    connect(ui->TransBtn, &QPushButton::clicked, this, &FeaturesWindow::goTransfer);
}

FeaturesWindow::~FeaturesWindow() {
    delete ui;
}
void FeaturesWindow::checkLoanStatus() {
    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("SELECT loan_status FROM accounts WHERE account_number = ?");
    query.addBindValue(accountNumber);

    if (query.exec() && query.next()) {
        QString loanStatus = query.value(0).toString();

        if (loanStatus == "unpaid") {
            ui->WithdrawBtn->setEnabled(false);
            ui->TransBtn->setEnabled(false);
            ui->AnnounceLabel->setText("Loan overdue! Withdraw & Transfer disabled.");
        } else {
            ui->WithdrawBtn->setEnabled(true);
            ui->TransBtn->setEnabled(true);
            ui->AnnounceLabel->clear();
        }
    }
}

void FeaturesWindow::goHomeBtn() {
    this->hide();

    MainBankGUI *gotoMainBankWin = new MainBankGUI(userName, accountNumber, accountBalance);
    gotoMainBankWin->setModal(true);
    gotoMainBankWin->exec();
    delete gotoMainBankWin;
}

void FeaturesWindow::goDeposit() {
    this->hide();

    DepositWindow *depositWin = new DepositWindow(userName, accountNumber, accountBalance);
    depositWin->setModal(true);
    depositWin->exec();
    delete depositWin;
}

void FeaturesWindow::goWithdraw(){
    this->hide();

    WithdrawWindow *withdrawwin = new WithdrawWindow(userName, accountNumber, accountBalance);
    withdrawwin->setModal(true);
    withdrawwin->exec();
    delete withdrawwin;
}
void FeaturesWindow::goTransfer(){
    this->hide();
    transferwindow *transferwin = new transferwindow(userName, accountNumber, accountBalance);
    transferwin->setModal(true);
    transferwin->exec();
    delete transferwin;
}
