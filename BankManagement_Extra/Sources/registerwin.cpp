#include "registerwin.h"
#include "mainwindow.h"
#include "ui_registerwin.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QRandomGenerator>

RegisterWin::RegisterWin(QWidget *parent)
    : QDialog(parent), ui(new Ui::RegisterWin) {
    ui->setupUi(this);
    ui->registerButton->setEnabled(false);

    connect(ui->usernameEdit, &QLineEdit::textChanged, this, &RegisterWin::validateInputs);
    connect(ui->passwordEdit, &QLineEdit::textChanged, this, &RegisterWin::validateInputs);
    connect(ui->registerButton, &QPushButton::clicked, this, &RegisterWin::handleRegistration);
    connect(ui->CancleBtn, &QPushButton::clicked, this, &RegisterWin::handlecanclebtn);
    connect(ui->confirmPasswordEdit, &QLineEdit::textChanged, this, &RegisterWin::validateInputs);
}

RegisterWin::~RegisterWin() {
    delete ui;
}

void RegisterWin::validateInputs() {
    bool enableButton = !ui->usernameEdit->text().isEmpty() &&
                        !ui->passwordEdit->text().isEmpty() &&
                        (ui->passwordEdit->text() == ui->confirmPasswordEdit->text());
    ui->registerButton->setEnabled(enableButton);
}

QString RegisterWin::generateAccountNumber() {
    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    QString number;
    //Generate Number and check if the number are duplicated or not. If not, insert the account number into the database.
    do {
        number.clear();
        for (int i = 0; i < 13; ++i) {
            number += QString::number(QRandomGenerator::global()->bounded(0, 10));
        }
        number.insert(4, '-').insert(10, '-');

        QString rawNumber = number;
        rawNumber.remove('-');

        query.prepare("SELECT COUNT(*) FROM accounts WHERE account_number = :accountNumber");
        query.bindValue(":accountNumber", rawNumber);
        query.exec();
        query.next();

    } while (query.value(0).toInt() > 0);  // If count > 0, generate again

    return number;
}


void RegisterWin::handleRegistration() {
    if (!DatabaseManager::getInstance()->getDatabase().isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database is not open.");
        return;
    }

    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    QSqlQuery checkUserQuery(DatabaseManager::getInstance()->getDatabase());
    checkUserQuery.prepare("SELECT COUNT(*) FROM accounts WHERE account_name = :username");
    checkUserQuery.bindValue(":username", username);

    if (checkUserQuery.exec() && checkUserQuery.next() && checkUserQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Registration Failed", "This username is already taken.");
        return;
    }

    QString accountNumber;
    QString rawAccountNumber;

    // Ensure unique account number
    bool isUnique = false;
    while (!isUnique) {
        accountNumber = generateAccountNumber();
        rawAccountNumber = accountNumber;
        rawAccountNumber.remove('-'); // Store without dashes

        QSqlQuery checkQuery(DatabaseManager::getInstance()->getDatabase());
        checkQuery.prepare("SELECT COUNT(*) FROM accounts WHERE account_number = :accountNumber");
        checkQuery.bindValue(":accountNumber", rawAccountNumber);
        if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() == 0) {
            isUnique = true;
        }
    }

    // Insert into database
    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("INSERT INTO accounts (account_name, account_number, account_password, account_balance, account_loan) VALUES (:username, :accountNumber, :password, 0, 0)");
    query.bindValue(":username", username);
    query.bindValue(":accountNumber", rawAccountNumber);
    query.bindValue(":password", password);

    if (query.exec()) {
        QString resultMessage = "Registration Successful!\nUsername: " + username + "\nAccount Number: " + accountNumber;
        QMessageBox::information(this, "Registration Successful", resultMessage);
        qDebug() << resultMessage;

        // Close registration window and reopen login window
        this->close();
        MainWindow *loginWin = new MainWindow();
        loginWin->show();
    } else {
        QString errorMessage = "Could not create account: " + query.lastError().text();
        QMessageBox::critical(this, "Registration Failed", errorMessage);
        qDebug() << errorMessage;
    }
}

void RegisterWin::handlecanclebtn(){
    this->close();
    MainWindow *loginwin = new MainWindow();
    loginwin->show();
}
