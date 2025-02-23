/********************************************************************************
** Form generated from reading UI file 'depositwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPOSITWINDOW_H
#define UI_DEPOSITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DepositWindow
{
public:
    QLabel *BalanceLabel;
    QLabel *AccNumLabel;
    QLabel *UsernamLabel;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *DepositWindow)
    {
        if (DepositWindow->objectName().isEmpty())
            DepositWindow->setObjectName("DepositWindow");
        DepositWindow->resize(570, 330);
        BalanceLabel = new QLabel(DepositWindow);
        BalanceLabel->setObjectName("BalanceLabel");
        BalanceLabel->setGeometry(QRect(30, 140, 481, 21));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        BalanceLabel->setFont(font);
        BalanceLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        AccNumLabel = new QLabel(DepositWindow);
        AccNumLabel->setObjectName("AccNumLabel");
        AccNumLabel->setGeometry(QRect(30, 80, 481, 21));
        AccNumLabel->setFont(font);
        AccNumLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        UsernamLabel = new QLabel(DepositWindow);
        UsernamLabel->setObjectName("UsernamLabel");
        UsernamLabel->setGeometry(QRect(30, 110, 481, 21));
        UsernamLabel->setFont(font);
        UsernamLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        label = new QLabel(DepositWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 0, 191, 51));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        label_2 = new QLabel(DepositWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 220, 91, 31));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        label_2->setFont(font2);
        lineEdit = new QLineEdit(DepositWindow);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(220, 220, 121, 31));
        pushButton = new QPushButton(DepositWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(360, 220, 121, 31));

        retranslateUi(DepositWindow);

        QMetaObject::connectSlotsByName(DepositWindow);
    } // setupUi

    void retranslateUi(QDialog *DepositWindow)
    {
        DepositWindow->setWindowTitle(QCoreApplication::translate("DepositWindow", "Dialog", nullptr));
        BalanceLabel->setText(QCoreApplication::translate("DepositWindow", "Balance:   10,212.00 THB", nullptr));
        AccNumLabel->setText(QCoreApplication::translate("DepositWindow", "Account Number: 1110-01023-4122", nullptr));
        UsernamLabel->setText(QCoreApplication::translate("DepositWindow", "Username:  Thanaphat", nullptr));
        label->setText(QCoreApplication::translate("DepositWindow", "Deposit Window", nullptr));
        label_2->setText(QCoreApplication::translate("DepositWindow", "Amount:", nullptr));
        pushButton->setText(QCoreApplication::translate("DepositWindow", "Confirm Deposit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DepositWindow: public Ui_DepositWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPOSITWINDOW_H
