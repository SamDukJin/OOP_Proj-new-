#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardItemModel>
#include "mainbankgui.h"

adminpanel::adminpanel(QWidget *parent)
    : QDialog(parent), ui(new Ui::adminpanel) {
    ui->setupUi(this);
    loadAccounts();

    connect(ui->HomeBtn, &QPushButton::clicked, this, &adminpanel::homebtn);
    connect(ui->DeactivateBtn, &QPushButton::clicked, this, &adminpanel::deactivateAccount);
    connect(ui->DelACCBtn, &QPushButton::clicked, this, &adminpanel::deleteAccount);
    connect(ui->ChangeNumBtn, &QPushButton::clicked, this, &adminpanel::changeaccnum);
    connect(ui->ActivateBtn, &QPushButton::clicked, this,&adminpanel::activateAccount);
}

adminpanel::~adminpanel() {
    delete ui;
}

void adminpanel::loadAccounts() {
    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("SELECT account_name, account_number, account_balance FROM accounts");

    if (!query.exec()) {
        qDebug() << "Failed to fetch accounts:" << query.lastError().text();
        return;
    }

    QAbstractItemModel *oldModel = ui->AccountTableView->model();
    if (oldModel) delete oldModel;

    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(3);
    model->setHorizontalHeaderLabels({"Username", "Account Number", "Balance (฿)"});

    while (query.next()) {
        QString name = query.value(0).toString();
        QString accNum = query.value(1).toString();
        double balance = query.value(2).toDouble();

        if (accNum.length() == 13) {
            accNum.insert(4, '-');
            accNum.insert(10, '-');
        }

        QList<QStandardItem *> rowItems;
        QStandardItem *nameItem = new QStandardItem(name);
        QStandardItem *accNumItem = new QStandardItem(accNum);
        QStandardItem *balanceItem = new QStandardItem(QString::number(balance, 'f', 2));

        // **Make the cells read-only**
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        accNumItem->setFlags(accNumItem->flags() & ~Qt::ItemIsEditable);
        balanceItem->setFlags(balanceItem->flags() & ~Qt::ItemIsEditable);

        rowItems.append(nameItem);
        rowItems.append(accNumItem);
        rowItems.append(balanceItem);
        model->appendRow(rowItems);
    }

    if (model->rowCount() == 0) {
        qDebug() << "No accounts found in the database.";
        return;
    }

    ui->AccountTableView->setModel(model);
}


void adminpanel::deactivateAccount() {
    QString accNum = ui->AN_inp->text().trimmed();
    if (accNum.isEmpty()) {
        qDebug() << "Account number input is empty.";
        return;
    }

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());

    // Check if the account exists
    query.prepare("SELECT status FROM accounts WHERE account_number = ?");
    query.addBindValue(accNum);
    if (!query.exec() || !query.next()) {
        qDebug() << "Account not found!";
        return;
    }

    QString currentStatus = query.value(0).toString();
    if (currentStatus == "deactivated") {
        qDebug() << "Account is already deactivated.";
        return;
    }

    // Update status to "deactivated"
    query.prepare("UPDATE accounts SET status = 'deactivated' WHERE account_number = ?");
    query.addBindValue(accNum);
    if (!query.exec()) {
        qDebug() << "Failed to deactivate account:" << query.lastError().text();
        return;
    }

    qDebug() << "Account" << accNum << "has been deactivated.";
    loadAccounts();  // Refresh account list
}

void adminpanel::deleteAccount() {
    QString accNum = ui->AN_inp->text().trimmed();
    if (accNum.isEmpty()) {
        qDebug() << "Account number input is empty.";
        return;
    }
    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("DELETE FROM accounts WHERE account_number = ?");
    query.addBindValue(accNum);

    if (!query.exec()) {
        qDebug() << "Failed to delete account:" << query.lastError().text();
        return;
    }
    qDebug() << "Account" << accNum << "has been deleted.";
    loadAccounts();
}

void adminpanel::changeaccnum() {
    QString oldAccNum = ui->AN_inp->text().trimmed();
    QString newAccNum = ui->AN_Change_inp->text().trimmed();

    if (oldAccNum.isEmpty() || newAccNum.isEmpty()) {
        qDebug() << "One or both account number fields are empty.";
        return;
    }

    QSqlQuery checkQuery(DatabaseManager::getInstance()->getDatabase());
    checkQuery.prepare("SELECT COUNT(*) FROM accounts WHERE account_number = ?");
    checkQuery.addBindValue(newAccNum);
    checkQuery.exec();
    checkQuery.next();
    if (checkQuery.value(0).toInt() > 0) {
        qDebug() << "Account number" << newAccNum << "already exists. Cannot change.";
        return;
    }

    QSqlQuery updateQuery(DatabaseManager::getInstance()->getDatabase());
    updateQuery.prepare("UPDATE accounts SET account_number = ? WHERE account_number = ?");
    updateQuery.addBindValue(newAccNum);
    updateQuery.addBindValue(oldAccNum);

    if (!updateQuery.exec()) {
        qDebug() << "Failed to change account number:" << updateQuery.lastError().text();
        return;
    }
    qDebug() << "Account number changed from" << oldAccNum << "to" << newAccNum;
    loadAccounts();
}

void adminpanel::activateAccount(){
    QString accNum = ui->AN_inp->text().trimmed();
    if (accNum.isEmpty()) {
        qDebug() << "Account number input is empty.";
        return;
    }

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());

    query.prepare("SELECT status FROM accounts WHERE account_number = ?");
    query.addBindValue(accNum);
    if (!query.exec() || !query.next()) {
        qDebug() << "Account not found!";
        return;
    }

    QString currentStatus = query.value(0).toString();
    if (currentStatus == "activated") {
        qDebug() << "Account is already activated.";
        return;
    }

    query.prepare("UPDATE accounts SET status = 'active' WHERE account_number = ?");
    query.addBindValue(accNum);
    if (!query.exec()) {
        qDebug() << "Failed to activate account:" << query.lastError().text();
        return;
    }

    qDebug() << "Account" << accNum << "has been activated.";
    loadAccounts();
}

void adminpanel::homebtn() {
    this->hide();

    MainBankGUI *mainBankGUIWin = new MainBankGUI("admin", "", 0.0);
    mainBankGUIWin->setModal(true);
    mainBankGUIWin->exec();

    delete mainBankGUIWin;
    this->close();
}
