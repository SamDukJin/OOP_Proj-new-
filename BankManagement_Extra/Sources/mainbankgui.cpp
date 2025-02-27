#include "mainbankgui.h"
#include "ui_mainbankgui.h"

#include "databasemanager.h"
#include "featureswindow.h"
#include "adminpanel.h"
#include "settingwindow.h"
#include "loanwindow.h"
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
    connect(ui->AdminPanelBtn, &QPushButton::clicked, this, &MainBankGUI::openAdminPanel);
    connect(ui->AccSettingBtn, &QPushButton::clicked, this, &MainBankGUI::openSetting);
    connect(ui->LoanBtn, &QPushButton::clicked, this, &MainBankGUI::openLoan);
}

MainBankGUI::~MainBankGUI() {
    delete ui;
}

void MainBankGUI::fetchUserDetails(const QString &username) {
    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
     // This block of code is just for the developer at backend only.

    // query.prepare("PRAGMA table_info(accounts);");
    // if (query.exec()) {
    //     while (query.next()) {
    //         QString columnName = query.value(1).toString(); // Column name is in index 1
    //         qDebug() << "Column:" << columnName;
    //     }
    // } else {
    //     qDebug() << "PRAGMA failed:" << query.lastError().text();
    // }

    // Only for checking the list of the data in the database.
    query.prepare("SELECT account_name, account_number, account_balance, account_password, status, account_loan FROM accounts WHERE account_name = ?");
    query.addBindValue(username);

    qDebug() << "Executing query:" << query.lastQuery();
    qDebug() << "Bound values:" << query.boundValues();
    qDebug() << "Database is open:" << DatabaseManager::getInstance()->getDatabase().isOpen();
    qDebug() << "Username:" << username;

    if (query.exec() && query.next()) {
        QString name = query.value(0).toString();
        QString accNum = query.value(1).toString();
        accountBalance = query.value(2).toDouble();
        password = query.value(3).toString();
        // double accountLoan = query.value(4).toDouble();
        QString status = query.value(5).toString();
        if (status == "deactivated") {
            ui->UsernamLabel->setVisible(false);
            ui->AccNumLabel->setVisible(false);
            ui->BalanceLabel->setVisible(false);
            ui->AnnounceLabel->setText("       Your Account has been Deactivated.\nPlease Contact Admin Via xxxx-xxxxx-xxxx.");

            for (QObject* child : this->children()) {
                QWidget* widget = qobject_cast<QWidget*>(child);
                if (widget) widget->setEnabled(false);
            }
            return;
        }
        if (accNum.length() == 13) {
            accNum.insert(4, '-');
            accNum.insert(10, '-');
        }

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

void MainBankGUI::openAdminPanel(){
    this->hide();
    adminpanel *adminwin = new adminpanel(this);
    adminwin->setModal(true);
    adminwin->exec();
}

void MainBankGUI::openSetting(){
    this->hide();
    SettingWindow *settingwin = new SettingWindow(userName, password, accountNumber, this);
    settingwin->setModal(true);
    settingwin->exec();
}

void MainBankGUI::openLoan() {
    this->hide();
    LoanWindow *loanWin = new LoanWindow(userName, accountNumber, accountBalance, this);
    loanWin->setModal(true);
    loanWin->exec();
}

