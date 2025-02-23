/********************************************************************************
** Form generated from reading UI file 'mainbankgui.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINBANKGUI_H
#define UI_MAINBANKGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MainBankGUI
{
public:
    QLabel *label;
    QLabel *BalanceLabel;
    QLabel *AccNumLabel;
    QLabel *UsernamLabel;
    QPushButton *ViewFeaturesBtn;
    QPushButton *LoanBtn;
    QPushButton *ViewRprtBtn;
    QPushButton *AccSettingBtn;

    void setupUi(QDialog *MainBankGUI)
    {
        if (MainBankGUI->objectName().isEmpty())
            MainBankGUI->setObjectName("MainBankGUI");
        MainBankGUI->resize(700, 500);
        MainBankGUI->setStyleSheet(QString::fromUtf8("QDialog{\n"
"	background-color: rgb(255, 162, 0)\n"
"}"));
        label = new QLabel(MainBankGUI);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 0, 301, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        BalanceLabel = new QLabel(MainBankGUI);
        BalanceLabel->setObjectName("BalanceLabel");
        BalanceLabel->setGeometry(QRect(30, 140, 481, 21));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        BalanceLabel->setFont(font1);
        BalanceLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        AccNumLabel = new QLabel(MainBankGUI);
        AccNumLabel->setObjectName("AccNumLabel");
        AccNumLabel->setGeometry(QRect(30, 80, 481, 21));
        AccNumLabel->setFont(font1);
        AccNumLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        UsernamLabel = new QLabel(MainBankGUI);
        UsernamLabel->setObjectName("UsernamLabel");
        UsernamLabel->setGeometry(QRect(30, 110, 481, 21));
        UsernamLabel->setFont(font1);
        UsernamLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        ViewFeaturesBtn = new QPushButton(MainBankGUI);
        ViewFeaturesBtn->setObjectName("ViewFeaturesBtn");
        ViewFeaturesBtn->setGeometry(QRect(290, 310, 121, 71));
        LoanBtn = new QPushButton(MainBankGUI);
        LoanBtn->setObjectName("LoanBtn");
        LoanBtn->setGeometry(QRect(450, 310, 121, 71));
        ViewRprtBtn = new QPushButton(MainBankGUI);
        ViewRprtBtn->setObjectName("ViewRprtBtn");
        ViewRprtBtn->setGeometry(QRect(130, 310, 121, 71));
        AccSettingBtn = new QPushButton(MainBankGUI);
        AccSettingBtn->setObjectName("AccSettingBtn");
        AccSettingBtn->setGeometry(QRect(560, 80, 111, 31));

        retranslateUi(MainBankGUI);

        QMetaObject::connectSlotsByName(MainBankGUI);
    } // setupUi

    void retranslateUi(QDialog *MainBankGUI)
    {
        MainBankGUI->setWindowTitle(QCoreApplication::translate("MainBankGUI", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("MainBankGUI", "Bank Management System", nullptr));
        BalanceLabel->setText(QCoreApplication::translate("MainBankGUI", "Balance:   10,212.00 THB", nullptr));
        AccNumLabel->setText(QCoreApplication::translate("MainBankGUI", "Account Number: 1110-01023-4122", nullptr));
        UsernamLabel->setText(QCoreApplication::translate("MainBankGUI", "Username:  Thanaphat", nullptr));
        ViewFeaturesBtn->setText(QCoreApplication::translate("MainBankGUI", "Features", nullptr));
        LoanBtn->setText(QCoreApplication::translate("MainBankGUI", "Loan Management", nullptr));
        ViewRprtBtn->setText(QCoreApplication::translate("MainBankGUI", "View Reports", nullptr));
        AccSettingBtn->setText(QCoreApplication::translate("MainBankGUI", "Account Setting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainBankGUI: public Ui_MainBankGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINBANKGUI_H
