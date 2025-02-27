#include "loanwindow.h"
#include "ui_loanwindow.h"
#include "mainbankgui.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

LoanWindow::LoanWindow(const QString &name, const QString &accountNum, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::LoanWindow), userName(name), accountNumber(accountNum), accountBalance(balance) {
    ui->setupUi(this);

    ui->UsernamLabel->setText("Username: " + userName);
    ui->AccNumLabel->setText("Account Number: " + accountNumber);
    ui->BalanceLabel->setText("Balance: " + QString::number(accountBalance, 'f', 2) + " ฿");

    connect(ui->HomeBtn, &QPushButton::clicked, this, &LoanWindow::homebtn);
    connect(ui->LoanBtn, &QPushButton::clicked, this, &LoanWindow::takeLoan);
    connect(ui->PayLoanBtn, &QPushButton::clicked, this, &LoanWindow::payloan);

    fetchLoanDetails(); // Retrieve loan information on load
}

LoanWindow::~LoanWindow() {
    delete ui;
}

void LoanWindow::fetchLoanDetails() {
    QString cleanedAccountNumber = accountNumber;
    cleanedAccountNumber.remove('-'); // Remove dashes if necessary

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

    totalLoan += loanAmount;  // Add loan to total
    updateDatabase(loanAmount);
}

void LoanWindow::updateDatabase(double loanAmount) {
    QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();

    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database is not open.");
        return;
    }

    QString cleanedAccountNumber = accountNumber;
    cleanedAccountNumber.remove('-'); // Ensure no dashes

    QSqlQuery query(db);
    query.prepare("UPDATE accounts SET account_balance = ?, account_loan = ? WHERE account_number = ?");

    // DO NOT add loanAmount separately, just update totalLoan and balance
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
    ui->BalanceLabel->setText("Balance: " + QString::number(accountBalance, 'f', 2) + " ฿");
    ui->loantakenLabel->setText("Total Loan Taken: " + QString::number(totalLoan, 'f', 2) + " ฿");

    if (totalLoan > 0) {
        ui->AnnounceLabel->setText("You have a pending loan of: " + QString::number(totalLoan, 'f', 2) +
                                   " ฿\nPay before the end of the month to avoid restrictions.");
    } else {
        ui->AnnounceLabel->clear();
    }
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

void LoanWindow::checkDueDate() {
    QDate currentDate = QDate::currentDate();
    int lastDayOfMonth = QDate(currentDate.year(), currentDate.month(), 1).daysInMonth();
    QDate dueDate(currentDate.year(), currentDate.month(), lastDayOfMonth);

    if (currentDate > dueDate) { // If overdue
        QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
        query.prepare("SELECT account_loan FROM accounts WHERE account_number = ?");
        query.addBindValue(accountNumber);

        if (query.exec() && query.next()) {
            double loanAmount = query.value(0).toDouble();

            if (loanAmount > 0) { // Loan exists and overdue
                query.prepare("UPDATE accounts SET loan_status = 'unpaid' WHERE account_number = ?");
                query.addBindValue(accountNumber);
                query.exec();
                ui->AnnounceLabel->setText("🚨 Loan overdue! Pay it to restore full access.");
            }
        }
    }
}

void LoanWindow::homebtn() {
    this->hide();
    MainBankGUI *mainbankguiwin = new MainBankGUI(userName, accountNumber, accountBalance);
    mainbankguiwin->setModal(true);
    mainbankguiwin->exec();
}
