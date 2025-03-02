#include "depositwindow.h"
#include "featureswindow.h"
#include "ui_depositwindow.h"
#include "databasemanager.h"
#include "utils.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

DepositWindow::DepositWindow(const QString &username, const QString &accountNumber, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::DepositWindow), userName(username), accNumber(accountNumber), accountBalance(balance)
{
    ui->setupUi(this);
    ui->UsernamLabel->setText("Username: "+username);
    ui->AccNumLabel->setText("Account Number: " + accNumber);
    ui->BalanceLabel->setText("Balance: " + formatBalance(accountBalance));

    connect(ui->ConfirmDepo, &QPushButton::clicked, this, &DepositWindow::handleDeposit);
    connect(ui->BackBtn, &QPushButton::clicked, this, &DepositWindow::goBack);
}

DepositWindow::~DepositWindow()
{
    delete ui;
}

void DepositWindow::handleDeposit(){
    bool ok;
    double depositAmount = ui->Amount_inp->text().toDouble(&ok);

    if (!ok || depositAmount <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid amount.");
        return;
    }
    QString formattedAccNum = accNumber;
    formattedAccNum.remove('-');

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("UPDATE accounts SET account_balance = account_balance + ? WHERE account_number = ?");
    query.addBindValue(depositAmount);
    query.addBindValue(formattedAccNum);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Deposit successful!");

        accountBalance += depositAmount;
        ui->BalanceLabel->setText("Balance: " + formatBalance(accountBalance));

        DatabaseManager::getInstance()->logTransaction(accNumber, "Deposit", depositAmount, "Deposited into account");

        ui->Amount_inp->clear();
    } else {
        QMessageBox::critical(this, "Error", "Failed to deposit: " + query.lastError().text());
    }
}


void DepositWindow::goBack() {
    this->hide();

    FeaturesWindow *featuresWin = new FeaturesWindow(userName, accNumber, accountBalance,this);
    featuresWin->setModal(true);
    featuresWin->exec();

    delete featuresWin;
    this->close();
}
