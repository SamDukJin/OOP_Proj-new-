#include "settingwindow.h"
#include "mainbankgui.h"
#include "ui_settingwindow.h"
#include "databasemanager.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

SettingWindow::SettingWindow(const QString &name, const QString &password,const QString &accountnumber, QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingWindow), userName(name), Password(password), accountNumber(accountnumber) {
    ui->setupUi(this);
    ui->UsernameLabel->setText("Username: " + userName);
    ui->PasswordLabel->setText("Password: " + Password);

    ui->UsernameChange->setPlaceholderText("To: ");
    ui->PasswordChange->setPlaceholderText("Enter new password");
    ui->PasswordChangeCon->setPlaceholderText("Confirm: ");

    connect(ui->PasswordChangeCon, &QLineEdit::textEdited, this, &SettingWindow::clearConfirmPlaceholder);

    connect(ui->ChangeUserNamBtn, &QPushButton::clicked, this, &SettingWindow::changeUsrNam);
    connect(ui->ChangePWBtn, &QPushButton::clicked, this, &SettingWindow::changePswd);
    connect(ui->LogoutBtn, &QPushButton::clicked, this, &SettingWindow::logout);
    connect(ui->DelAcc, &QPushButton::clicked, this, &SettingWindow::delAcc);
    connect(ui->HomeBtn, &QPushButton::clicked, this, &SettingWindow::gohome);
}


SettingWindow::~SettingWindow() {
    delete ui;
}

void SettingWindow::changeUsrNam() {
    QString newUsername = ui->UsernameChange->text().trimmed();
    if (newUsername.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username cannot be empty.");
        return;
    }

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("UPDATE accounts SET account_name = ? WHERE account_name = ?");
    query.addBindValue(newUsername);
    query.addBindValue(userName);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Username updated successfully.");
        userName = newUsername;
        ui->UsernameLabel->setText("Username: " + userName);
    } else {
        QMessageBox::critical(this, "Error", "Failed to update username: " + query.lastError().text());
    }
}

void SettingWindow::changePswd() {
    QString newPassword = ui->PasswordChange->text();
    QString confirmPassword = ui->PasswordChangeCon->text();

    if (newPassword != confirmPassword) {
        QMessageBox::warning(this, "Error", "Passwords do not match.");
        return;
    }

    QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
    query.prepare("UPDATE accounts SET account_password = ? WHERE account_name = ?");
    query.addBindValue(newPassword);
    query.addBindValue(userName);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Password updated successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to update password: " + query.lastError().text());
    }
}

void SettingWindow::logout() {
    QMessageBox::information(this, "Logout", "You have been logged out.");
    this->close();
    MainWindow *mainWin = new MainWindow();
    mainWin->show();
}

void SettingWindow::delAcc() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete your account?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query(DatabaseManager::getInstance()->getDatabase());
        query.prepare("DELETE FROM accounts WHERE account_name = ?");
        query.addBindValue(userName);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Successfully deleted your account!");
            this->close();
            MainWindow *mainWin = new MainWindow();
            mainWin->show();
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete account: " + query.lastError().text());
        }
    }
}

void SettingWindow::clearConfirmPlaceholder() {
    if (ui->PasswordChangeCon->text() == "Confirm: ") {
        ui->PasswordChangeCon->clear();
    }
}


void SettingWindow::gohome(){
    this->hide();
    MainBankGUI *mainwindow = new MainBankGUI(userName,accountNumber,0.0,this);
    mainwindow->setModal(true);
    mainwindow->exec();
}
