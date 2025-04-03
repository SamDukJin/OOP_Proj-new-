#include "showrecwindow.h"
#include "ui_showrecwindow.h"
#include "mainbankgui.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>

ShowRecWindow::ShowRecWindow(const QString &name, const QString &accountNum, double balance, QWidget *parent)
    : QDialog(parent), ui(new Ui::ShowRecWindow), userName(name), accountNumber(accountNum), accountBalance(balance), model(nullptr)
{
    ui->setupUi(this);

    connect(ui->HomeBtn, &QPushButton::clicked, this, &ShowRecWindow::homebtn);

    loadTransactionHistory();
}

ShowRecWindow::~ShowRecWindow()
{
    delete model;
    delete ui;
}

void ShowRecWindow::homebtn()
{
    this->hide();
    MainBankGUI *maingui = new MainBankGUI(userName, accountNumber, accountBalance,this);
    maingui->setModal(true);
    maingui->exec();
}

void ShowRecWindow::loadTransactionHistory()
{
    DatabaseManager* dbManager = DatabaseManager::getInstance();
    if (!dbManager) {
        qDebug() << "DatabaseManager instance is null!";
        return;
    }

    delete model;
    model = new QSqlTableModel(this, dbManager->getDatabase());

    model->setTable("transactions");
    model->setFilter("account_number = '" + accountNumber + "'");
    model->setSort(5, Qt::DescendingOrder);
    model->select();

    if (model->rowCount() == 0) {
        qDebug() << "No transactions found for this account.";
    }

    // Set column headers
    model->setHeaderData(2, Qt::Horizontal, "Type");
    model->setHeaderData(3, Qt::Horizontal, "Amount");
    model->setHeaderData(4, Qt::Horizontal, "Details");
    model->setHeaderData(5, Qt::Horizontal, "Date");

    // Configure tableView
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Adjust column size
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
}
