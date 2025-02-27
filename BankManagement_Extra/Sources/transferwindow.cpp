#include "transferwindow.h"
#include "ui_transferwindow.h"
#include "databasemanager.h"
#include "featureswindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

transferwindow::transferwindow(const QString &username, const QString &accountNumber, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::transferwindow), userName(username), accountNum(accountNumber), balance(balance)
{
    ui->setupUi(this);
    ui->UsernamLabel->setText("Username: "+ userName);
    ui->AccNumLabel->setText("Account Number: " + accountNumber);
    ui->BalanceLabel->setText("Balance: " + QString::number(balance, 'f', 2) + " ฿");

    connect(ui->AccNumSelect, &QLineEdit::textChanged, this, &transferwindow::checkAccountAvailability);
    connect(ui->TransferBtn, &QPushButton::clicked, this, &transferwindow::processTransfer);
    connect(ui->HomeBtn, &QPushButton::clicked, this, &transferwindow::homebtn);
}


transferwindow::~transferwindow()
{
    delete ui;
}

//Constantly checking the account if exist everytime user key in the account number (without -)
void transferwindow::checkAccountAvailability() {
    QString recipientAcc = ui->AccNumSelect->text().trimmed();
    if (recipientAcc.isEmpty()) {
        ui->StatusLabel->setText("Not available! Account not exist!");
        return;
    }

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("SELECT account_name FROM accounts WHERE account_number = ?");
    query.addBindValue(recipientAcc);

    if (query.exec() && query.next()) {
        ui->StatusLabel->setText("Available!");
    } else {
        ui->StatusLabel->setText("Not available! Account not exist!");
    }
}

void transferwindow::processTransfer() {
    QString recipientAcc = ui->AccNumSelect->text().trimmed();
    double transferAmount = ui->AmountSelect->text().toDouble();

    if (recipientAcc.isEmpty() || transferAmount <= 0) {
        ui->StatusLabel->setText("Error");
        QMessageBox::warning(this, "Error", "Invalid account number or amount.");
        return;
    }

    if (transferAmount > balance) {
        QMessageBox::warning(this, "Error", "Insufficient balance!");
        return;
    }
    // This to make sure to unformat the formatted account number (remove the -)
    QString senderAccFormatted = accountNum;
    senderAccFormatted.remove('-');
    recipientAcc.remove('-');

    QSqlQuery checkQuery(DatabaseManager::getInstance()->getDatabase());
    checkQuery.prepare("SELECT account_balance FROM accounts WHERE account_number = ?");
    checkQuery.addBindValue(recipientAcc);

    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::warning(this, "Error", "Recipient account not found.");
        return;
    }
    //Key in the sender and the receiver balance. Make sure everything is valid.
    double recipientBalance = checkQuery.value(0).toDouble();
    double newSenderBalance = balance - transferAmount;
    double newRecipientBalance = recipientBalance + transferAmount;

    QSqlQuery updateSender(DatabaseManager::getInstance()->getDatabase());
    updateSender.prepare("UPDATE accounts SET account_balance = ? WHERE account_number = ?");
    updateSender.addBindValue(newSenderBalance);
    updateSender.addBindValue(senderAccFormatted);

    QSqlQuery updateRecipient(DatabaseManager::getInstance()->getDatabase());
    updateRecipient.prepare("UPDATE accounts SET account_balance = ? WHERE account_number = ?");
    updateRecipient.addBindValue(newRecipientBalance);
    updateRecipient.addBindValue(recipientAcc);

    // Start transaction
    DatabaseManager::getInstance()->getDatabase().transaction();

    if (updateSender.exec() && updateRecipient.exec()) {
        DatabaseManager::getInstance()->getDatabase().commit();
        QMessageBox::information(this, "Success", "Transfer successful!");

        // **Explicitly Refresh Balance from Database**
        QSqlQuery refreshBalance(DatabaseManager::getInstance()->getDatabase());
        refreshBalance.prepare("SELECT account_balance FROM accounts WHERE account_number = ?");
        refreshBalance.addBindValue(senderAccFormatted);

        qDebug() << "Refreshing balance for account number:" << senderAccFormatted;

        if (!refreshBalance.exec()) {
            qDebug() << "Balance refresh query failed:" << refreshBalance.lastError().text();
            QMessageBox::warning(this, "Error", "Could not refresh balance.");
            return;
        }

        if (refreshBalance.next()) {
            balance = refreshBalance.value(0).toDouble();
            ui->BalanceLabel->setText("Balance: " + QString::number(balance, 'f', 2) + " ฿");
            qDebug() << "Balance updated to:" << balance;
        } else {
            qDebug() << "No result found for balance refresh! Account tried:" << senderAccFormatted;
            QMessageBox::warning(this, "Error", "Could not refresh balance.");
        }
    } else {
        DatabaseManager::getInstance()->getDatabase().rollback(); // Rollback if update failed
        qDebug() << "Transfer failed:" << updateSender.lastError().text() << " | " << updateRecipient.lastError().text();
        QMessageBox::critical(this, "Error", "Transfer failed!");
    }
}

void transferwindow::homebtn(){
    this->hide();
    FeaturesWindow *featureswin = new FeaturesWindow(userName,accountNum,balance,this);
    featureswin->setModal(true);
    featureswin->exec();
}
