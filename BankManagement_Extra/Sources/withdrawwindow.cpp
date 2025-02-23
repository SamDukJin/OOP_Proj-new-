#include "withdrawwindow.h"
#include "ui_withdrawwindow.h"
#include "featureswindow.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

WithdrawWindow::WithdrawWindow(const QString &username, const QString &accountNumber, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::WithdrawWindow), userName(username), accNumber(accountNumber), accBalance(balance) {
    ui->setupUi(this);

    // Display initial balance and account number
    ui->AccNumLabel->setText("Account Number: " + accNumber);
    ui->BalanceLabel->setText("Balance: " + QString::number(accBalance, 'f', 2) + " ฿");

    // Connect buttons to functions
    connect(ui->ConfirmWith, &QPushButton::clicked, this, &WithdrawWindow::handleWithdraw);
    connect(ui->BackBtn, &QPushButton::clicked, this, &WithdrawWindow::goBack);
}

WithdrawWindow::~WithdrawWindow() {
    delete ui;
}

void WithdrawWindow::handleWithdraw() {
    bool ok;
    double withdrawAmount = ui->Amount_inp->text().toDouble(&ok);

    // Validate input
    if (!ok || withdrawAmount <= 0 || withdrawAmount > accBalance) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid amount.");
        return;
    }

    // Update the database
    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("UPDATE accounts SET account_balance = account_balance - ? WHERE account_name = ?");
    query.addBindValue(withdrawAmount);
    query.addBindValue(userName);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Withdrawal successful!");

        // Update local balance and refresh display
        accBalance -= withdrawAmount;
        updateBalanceDisplay();

        ui->Amount_inp->clear();  // Clear input field after withdrawal
    } else {
        QMessageBox::critical(this, "Error", "Failed to withdraw: " + query.lastError().text());
    }
}

void WithdrawWindow::updateBalanceDisplay() {
    ui->BalanceLabel->setText("Balance: " + QString::number(accBalance, 'f', 2) + " ฿");
}

void WithdrawWindow::goBack() {
    this->hide();

    FeaturesWindow *featuresWin = new FeaturesWindow(userName, accNumber, accBalance);
    featuresWin->setModal(true);
    featuresWin->exec();

    delete featuresWin;
    this->close();
}
