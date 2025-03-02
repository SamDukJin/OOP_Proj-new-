#include "transferwindow.h"
#include "ui_transferwindow.h"
#include "databasemanager.h"
#include "featureswindow.h"
#include "utils.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

transferwindow::transferwindow(const QString &username, const QString &accountNumber, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::transferwindow), userName(username), accountNum(accountNumber), accountBalance(balance)
{
    ui->setupUi(this);
    ui->UsernamLabel->setText("Username: " + userName);
    ui->AccNumLabel->setText("Account Number: " + accountNumber);
    ui->BalanceLabel->setText("Balance: " + formatBalance(accountBalance));

    connect(ui->AccNumSelect, &QLineEdit::textChanged, this, &transferwindow::checkAccountAvailability);
    connect(ui->TransferBtn, &QPushButton::clicked, this, &transferwindow::processTransfer);
    connect(ui->HomeBtn, &QPushButton::clicked, this, &transferwindow::homebtn);
}

transferwindow::~transferwindow()
{
    delete ui;
}

// Constantly checking if the account exists whenever the user enters an account number
void transferwindow::checkAccountAvailability() {
    QString recipientAcc = ui->AccNumSelect->text().trimmed();
    if (recipientAcc.isEmpty()) {
        ui->StatusLabel->setText("Status: Not available!\nAccount does not exist!");
        return;
    }

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("SELECT account_name FROM accounts WHERE account_number = ?");
    query.addBindValue(recipientAcc);

    if (query.exec() && query.next()) {
        ui->StatusLabel->setText("Available!");
    } else {
        ui->StatusLabel->setText("Status: Not available!\nAccount does not exist!");
    }
}

void transferwindow::processTransfer() {
    QString recipientAcc = ui->AccNumSelect->text().trimmed();
    double transferAmount = ui->AmountSelect->text().toDouble();

    QLocale locale(QLocale::English);

    if (recipientAcc.isEmpty() || transferAmount <= 0) {
        ui->StatusLabel->setText("Error");
        QMessageBox::warning(this, "Error", "Invalid account number or amount.");
        return;
    }

    if (transferAmount > accountBalance) {
        QMessageBox::warning(this, "Error", "Insufficient balance!");
        return;
    }

    QString senderAccFormatted = accountNum;
    senderAccFormatted.remove('-');
    recipientAcc.remove('-');

    QSqlQuery checkQuery(DatabaseManager::getInstance()->getDatabase());
    checkQuery.prepare("SELECT account_name, account_balance FROM accounts WHERE account_number = ?");
    checkQuery.addBindValue(recipientAcc);

    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::warning(this, "Error", "Recipient account not found.");
        return;
    }

    QString recipientName = checkQuery.value(0).toString();
    double recipientBalance = checkQuery.value(1).toDouble();
    double newSenderBalance = accountBalance - transferAmount;
    double newRecipientBalance = recipientBalance + transferAmount;

    QSqlQuery updateSender(DatabaseManager::getInstance()->getDatabase());
    updateSender.prepare("UPDATE accounts SET account_balance = ? WHERE account_number = ?");
    updateSender.addBindValue(newSenderBalance);
    updateSender.addBindValue(senderAccFormatted);

    QSqlQuery updateRecipient(DatabaseManager::getInstance()->getDatabase());
    updateRecipient.prepare("UPDATE accounts SET account_balance = ? WHERE account_number = ?");
    updateRecipient.addBindValue(newRecipientBalance);
    updateRecipient.addBindValue(recipientAcc);

    DatabaseManager::getInstance()->getDatabase().transaction();

    if (updateSender.exec() && updateRecipient.exec()) {
        DatabaseManager::getInstance()->getDatabase().commit();

        DatabaseManager::getInstance()->logTransaction(accountNum, "Transfer Out", transferAmount, "Transferred to " + recipientAcc);
        DatabaseManager::getInstance()->logTransaction(recipientAcc, "Transfer In", transferAmount, "Received from " + accountNum);

        QString formattedRecipientAcc = recipientAcc;
        formattedRecipientAcc.insert(4, "-").insert(10, "-");

        QString successMessage = QString(
                                     "Transfer Successful!\nTo User: %1.\nAccount Number: %2.\nAmount: %3 ฿"
                                     ).arg(recipientName, formattedRecipientAcc, locale.toString(transferAmount, 'f', 2));

        QMessageBox::information(this, "Success", successMessage);

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
            accountBalance = refreshBalance.value(0).toDouble();
            ui->BalanceLabel->setText("Balance: " + formatBalance(accountBalance));
            qDebug() << "Balance updated to:" << accountBalance;
        } else {
            qDebug() << "No result found for balance refresh! Account tried:" << senderAccFormatted;
            QMessageBox::warning(this, "Error", "Could not refresh balance.");
        }
    } else {
        DatabaseManager::getInstance()->getDatabase().rollback();
        qDebug() << "Transfer failed:" << updateSender.lastError().text() << " | " << updateRecipient.lastError().text();
        QMessageBox::critical(this, "Error", "Transfer failed!");
    }
}
void transferwindow::homebtn(){
    this->hide();
    FeaturesWindow *featureswin = new FeaturesWindow(userName, accountNum, accountBalance, this);
    featureswin->setModal(true);
    featureswin->exec();
}
