#include "mainwindow.h"
#include "mainbankgui.h"
#include "registerwin.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->LoginBtn, &QPushButton::clicked, this, &MainWindow::handleLogin);
    connect(ui->RegisterBtn_2, &QPushButton::clicked, this, &MainWindow::handleregister);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::handleLogin() {
    if (!DatabaseManager::getInstance()->getDatabase().isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database is not open.");
        return;
    }

    QString username = ui->Usnam_inp->text();
    QString password = ui->Pswrd_inp->text();

    // Admin check first
    if (username == "admin" && password == "admin123") {
        qDebug() << "Welcome, admin!";
        QString message = "Welcome " + username + "!";
        QMessageBox::information(this, "Login Successful", message);

        this->hide();
        MainBankGUI *bankGUI = new MainBankGUI(username, "0000-00000-0000", 0.0);
        bankGUI->setModal(true);
        bankGUI->exec();
        delete bankGUI;
        this->close();
        return;
    }

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("SELECT account_number, account_balance FROM accounts WHERE account_name = :username AND account_password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        QString rawAccountNumber = query.value(0).toString();
        double accountBalance = query.value(1).toDouble();

        QString formattedAccountNumber = rawAccountNumber;
        formattedAccountNumber.insert(4, '-').insert(10, '-');

        QString message = "Welcome " + username + "! Account number: " + formattedAccountNumber;
        qDebug() << message;
        QMessageBox::information(this, "Login Successful", message);

        this->hide();
        MainBankGUI *bankGUI = new MainBankGUI(username, formattedAccountNumber, accountBalance);
        bankGUI->setModal(true);
        bankGUI->exec();
        delete bankGUI;
        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}


void MainWindow::handleregister(){
    this->hide();
    RegisterWin *registerWin = new RegisterWin();
    registerWin->setModal(true);
    registerWin->exec();
    delete registerWin;
    this->close();
}
