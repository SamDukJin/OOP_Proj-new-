#include "loanwindow.h"
#include "ui_loanwindow.h"
#include "mainbankgui.h"
#include "databasemanager.h"
#include "utils.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

LoanWindow::LoanWindow(const QString &name, const QString &accountNum, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::LoanWindow), userName(name), accountNumber(accountNum), accountBalance(balance) {
    ui->setupUi(this);

    ui->UsernamLabel->setText("Username: " + userName);
    ui->AccNumLabel->setText("Account Number: " + accountNumber);
    ui->BalanceLabel->setText("Balance: " + formatBalance(accountBalance));

    connect(ui->HomeBtn, &QPushButton::clicked, this, &LoanWindow::homebtn);
    connect(ui->LoanBtn, &QPushButton::clicked, this, &LoanWindow::takeLoan);
    connect(ui->PayLoanBtn, &QPushButton::clicked, this, &LoanWindow::payloan);

    fetchLoanDetails();
}

LoanWindow::~LoanWindow() {
    delete ui;
}

void LoanWindow::fetchLoanDetails() {
    QString cleanedAccountNumber = accountNumber;
    cleanedAccountNumber.remove('-');

    qDebug() << "Fetching loan details for account: " << cleanedAccountNumber;

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("SELECT COALESCE(account_loan, 0) FROM accounts WHERE account_number = ?");
    query.addBindValue(cleanedAccountNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Query execution failed: " + query.lastError().text());
        return;
    }

    if (query.next()) {
        totalLoan = query.value(0).toDouble();
        updateUI();
    } else {
        QMessageBox::critical(this, "Error", "No loan record found for this account.");
    }
}

void LoanWindow::takeLoan() {
    double loanAmount = ui->comboBox->currentText().toDouble();

    if (loanAmount <= 0) {
        QMessageBox::warning(this, "Invalid Amount", "Please select a valid loan amount.");
        return;
    }

    if (totalLoan >= 10000) {
        QMessageBox::warning(this, "Loan Limit Reached", "You cannot take more loans until you repay your existing debt.");
        ui->AnnounceLabel->clear();
        ui->AnnounceLabel->setText("Loan Limit reached: 10,000 ฿.\nMust pay the loan to perform next loan.");
        return;
    }

    if (totalLoan + loanAmount > 10000) {
        QMessageBox::warning(this, "Loan Exceeds Limit", "You can only take a loan up to 10,000 ฿. Reduce the amount.");
        ui->AnnounceLabel->clear();
        ui->AnnounceLabel->setText("Loan Limit reached: 10,000 ฿.\nMust pay the loan to perform next loan.");
        return;
    }

    totalLoan += loanAmount;
    updateDatabase(loanAmount);
}

void LoanWindow::updateDatabase(double loanAmount) {
    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();

    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database is not open.");
        return;
    }

    QString cleanedAccountNumber = accountNumber;
    cleanedAccountNumber.remove('-');

    QSqlQuery query(db);
    query.prepare("UPDATE accounts SET account_balance = ?, account_loan = ? WHERE account_number = ?");

    double newBalance = accountBalance + loanAmount;
    query.addBindValue(newBalance);
    query.addBindValue(totalLoan);
    query.addBindValue(cleanedAccountNumber);

    if (query.exec()) {
        db.commit();
        accountBalance = newBalance;
        updateUI();
        QMessageBox::information(this, "Loan Approved", "Loan successfully added to your balance.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to update loan details: " + query.lastError().text());
    }
}

void LoanWindow::updateUI() {
    ui->BalanceLabel->setText("Balance: " + formatBalance(accountBalance));
    ui->loantakenLabel->setText("Total Loan Taken: " + formatBalance(accountBalance));

    if (totalLoan >= 10000) {
        ui->AnnounceLabel->setText("Loan Limit reached: 10,000 ฿.\nMust pay the loan to perform next loan.");
    } else if (totalLoan > 0) {
        ui->AnnounceLabel->setText("You have a pending loan of: " +formatBalance(accountBalance) +
                                   " ฿\nMust not exceed 10,000 ฿.");
    } else {
        ui->AnnounceLabel->clear();
    }

    ui->LoanBtn->setEnabled(totalLoan < 10000);
}
void LoanWindow::payloan() {
    if (totalLoan <= 0) {
        QMessageBox::information(this, "No Loan", "You have no loan to pay.");
        return;
    }

    if (accountBalance < totalLoan) {
        QMessageBox::warning(this, "Insufficient Funds", "You don't have enough balance to pay the loan.");
        return;
    }

    accountBalance -= totalLoan;
    totalLoan = 0;

    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database is not open.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE accounts SET account_balance = ?, account_loan = 0, loan_status = 'paid' WHERE account_number = ?");
    query.addBindValue(accountBalance);
    QString cleanedAccountNumber = accountNumber;
    cleanedAccountNumber.remove('-');
    query.addBindValue(cleanedAccountNumber);

    qDebug() << "Executing loan payment update query...";
    qDebug() << "New Balance: " << accountBalance << ", Loan Cleared: " << totalLoan;
    qDebug() << "Account Number: " << accountNumber;

    if (query.exec()) {
        db.commit();
        QMessageBox::information(this, "Loan Paid", "Your loan has been fully paid!");
        updateUI();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update loan status: " + query.lastError().text());
        qDebug() << "SQL Error: " << query.lastError().text();
    }
}



void LoanWindow::homebtn() {
    this->hide();
    MainBankGUI *mainbankguiwin = new MainBankGUI(userName, accountNumber, accountBalance,this);
    mainbankguiwin->setModal(true);
    mainbankguiwin->exec();
}
