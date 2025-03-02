#include "withdrawwindow.h"
#include "ui_withdrawwindow.h"
#include "featureswindow.h"
#include "databasemanager.h"
#include "utils.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

WithdrawWindow::WithdrawWindow(const QString &username, const QString &accountNumber, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::WithdrawWindow), userName(username), accNumber(accountNumber), accountBalance(balance) {
    ui->setupUi(this);
    ui->AccNumLabel->setText("Account Number: " + accNumber);
    ui->BalanceLabel->setText("Balance: " + formatBalance(accountBalance));

    connect(ui->ConfirmWith, &QPushButton::clicked, this, &WithdrawWindow::handleWithdraw);
    connect(ui->BackBtn, &QPushButton::clicked, this, &WithdrawWindow::goBack);
}

WithdrawWindow::~WithdrawWindow() {
    delete ui;
}

void WithdrawWindow::handleWithdraw() {
    bool ok;
    double withdrawAmount = ui->Amount_inp->text().toDouble(&ok);

    if (!ok || withdrawAmount <= 0 || withdrawAmount > accountBalance) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid amount.");
        return;
    }

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("UPDATE accounts SET account_balance = account_balance - ? WHERE account_name = ?");
    query.addBindValue(withdrawAmount);
    query.addBindValue(userName);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Withdrawal successful!");

        accountBalance -= withdrawAmount;
        ui->BalanceLabel->setText("Balance: " + formatBalance(accountBalance));
        DatabaseManager::getInstance()->logTransaction(accNumber, "Withdraw", withdrawAmount, "Withdrawn from account");

        ui->Amount_inp->clear();
    } else {
        QMessageBox::critical(this, "Error", "Failed to withdraw: " + query.lastError().text());
    }
}
void WithdrawWindow::goBack() {
    this->hide();

    FeaturesWindow *featuresWin = new FeaturesWindow(userName, accNumber, accountBalance,this);
    featuresWin->setModal(true);
    featuresWin->exec();

    delete featuresWin;
    this->close();
}
