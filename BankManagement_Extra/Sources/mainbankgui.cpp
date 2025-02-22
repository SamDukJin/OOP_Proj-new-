#include "mainbankgui.h"
#include "ui_mainbankgui.h"
#include "databasemanager.h"
#include "featureswindow.h"
#include <QSqlQuery>
#include "mainbankgui.h"
#include "ui_mainbankgui.h"
#include "databasemanager.h"
#include "featureswindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

MainBankGUI::MainBankGUI(const QString &username, const QString &accountNumber, double accountBalance, QWidget *parent)
    : QDialog(parent), ui(new Ui::MainBankGUI), userName(username), accountNumber(accountNumber), accountBalance(accountBalance) {
    ui->setupUi(this);
    if (username == "admin") {
        ui->AdminPanelBtn->setVisible(true);
        ui->BalanceLabel->setVisible(false);
        ui->UsernamLabel->setText("Welcome Admin!");
        ui->AccNumLabel->setVisible(false);
    } else {
        ui->AdminPanelBtn->setVisible(false);
        fetchUserDetails(username);
    }

    connect(ui->ViewFeaturesBtn, &QPushButton::clicked, this, &MainBankGUI::openFeaturesWindow);
}

MainBankGUI::~MainBankGUI() {
    delete ui;
}

void MainBankGUI::fetchUserDetails(const QString &username) {
    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    // query.prepare("PRAGMA table_info(accounts);");

    // if (query.exec()) {
    //     while (query.next()) {
    //         QString columnName = query.value(1).toString(); // Column name is in index 1
    //         qDebug() << "Column:" << columnName;
    //     }
    // } else {
    //     qDebug() << "PRAGMA failed:" << query.lastError().text();
    // }
    query.prepare("SELECT account_name, account_number, account_balance FROM accounts WHERE account_name = ?");
    query.addBindValue(username);

    qDebug() << "Executing query:" << query.lastQuery();
    qDebug() << "Bound values:" << query.boundValues();
    qDebug() << "Database is open:" << DatabaseManager::getInstance()->getDatabase().isOpen();
    qDebug() << "Username:" << username;

    if (query.exec() && query.next()) {
        QString name = query.value(0).toString();
        QString accNum = query.value(1).toString();
        accountBalance = query.value(2).toDouble();

        ui->UsernamLabel->setText("Account Name: " + name);
        ui->AccNumLabel->setText("Account Number: " + accNum);
        ui->BalanceLabel->setText("Balance: " + QString::number(accountBalance, 'f', 2) + " ฿");
    } else {
        QMessageBox::critical(this, "Error", "Failed to fetch user information.");
    }
}
void MainBankGUI::openFeaturesWindow() {
    this->hide();
    FeaturesWindow *featuresWin = new FeaturesWindow(userName, accountNumber, accountBalance, this);
    featuresWin->setModal(true);
    featuresWin->exec();
}
