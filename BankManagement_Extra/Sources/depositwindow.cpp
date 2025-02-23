#include "depositwindow.h"
#include "featureswindow.h"
#include "ui_depositwindow.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

DepositWindow::DepositWindow(const QString &username, const QString &accountNumber, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::DepositWindow), userName(username), accNumber(accountNumber), accBalance(balance)
{
    ui->setupUi(this);

    // Display initial balance and account number
    ui->UsernamLabel->setText("Username: "+username);
    ui->AccNumLabel->setText("Account Number: " + accNumber);
    ui->BalanceLabel->setText("Balance: " + QString::number(accBalance, 'f', 2) + " ฿");

    // Connect buttons to functions
    connect(ui->ConfirmDepo, &QPushButton::clicked, this, &DepositWindow::handleDeposit);
    connect(ui->BackBtn, &QPushButton::clicked, this, &DepositWindow::goBack);
}

DepositWindow::~DepositWindow()
{
    delete ui;
}

void DepositWindow::handleDeposit()
{
    bool ok;
    double depositAmount = ui->Amount_inp->text().toDouble(&ok);

    // Validate input
    if (!ok || depositAmount <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid amount.");
        return;
    }

    // Update the database
    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("UPDATE accounts SET account_balance = account_balance + ? WHERE account_name = ?");
    query.addBindValue(depositAmount);
    query.addBindValue(userName);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Deposit successful!");

        // Update local balance and refresh display
        accBalance += depositAmount;
        updateBalanceDisplay();

        ui->Amount_inp->clear();  // Clear input field after deposit
    } else {
        QMessageBox::critical(this, "Error", "Failed to deposit: " + query.lastError().text());
    }
}

void DepositWindow::updateBalanceDisplay()
{
    ui->BalanceLabel->setText("Balance: " + QString::number(accBalance, 'f', 2) + " ฿");
}

void DepositWindow::goBack() {
    this->hide();  // Hide current window

    FeaturesWindow *featuresWin = new FeaturesWindow(userName, accNumber, accBalance);
    featuresWin->setModal(true);
    featuresWin->exec();

    delete featuresWin;
    this->close();
}
