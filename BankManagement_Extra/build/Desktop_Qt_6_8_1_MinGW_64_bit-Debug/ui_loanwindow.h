/********************************************************************************
** Form generated from reading UI file 'loanwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOANWINDOW_H
#define UI_LOANWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoanWindow
{
public:
    QLabel *label;
    QLabel *AccNumLabel;
    QLabel *UsernamLabel;
    QLabel *BalanceLabel;
    QLabel *BalanceLabel_2;
    QPushButton *pushButton;

    void setupUi(QDialog *LoanWindow)
    {
        if (LoanWindow->objectName().isEmpty())
            LoanWindow->setObjectName("LoanWindow");
        LoanWindow->resize(700, 500);
        label = new QLabel(LoanWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(270, 0, 161, 71));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        label->setFont(font);
        AccNumLabel = new QLabel(LoanWindow);
        AccNumLabel->setObjectName("AccNumLabel");
        AccNumLabel->setGeometry(QRect(40, 80, 481, 21));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        AccNumLabel->setFont(font1);
        AccNumLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        UsernamLabel = new QLabel(LoanWindow);
        UsernamLabel->setObjectName("UsernamLabel");
        UsernamLabel->setGeometry(QRect(40, 110, 481, 21));
        UsernamLabel->setFont(font1);
        UsernamLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        BalanceLabel = new QLabel(LoanWindow);
        BalanceLabel->setObjectName("BalanceLabel");
        BalanceLabel->setGeometry(QRect(40, 140, 481, 21));
        BalanceLabel->setFont(font1);
        BalanceLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        BalanceLabel_2 = new QLabel(LoanWindow);
        BalanceLabel_2->setObjectName("BalanceLabel_2");
        BalanceLabel_2->setGeometry(QRect(40, 180, 481, 21));
        BalanceLabel_2->setFont(font1);
        BalanceLabel_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        pushButton = new QPushButton(LoanWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 390, 131, 41));

        retranslateUi(LoanWindow);

        QMetaObject::connectSlotsByName(LoanWindow);
    } // setupUi

    void retranslateUi(QDialog *LoanWindow)
    {
        LoanWindow->setWindowTitle(QCoreApplication::translate("LoanWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoanWindow", "Loan Window", nullptr));
        AccNumLabel->setText(QCoreApplication::translate("LoanWindow", "Account Number: 1110-01023-4122", nullptr));
        UsernamLabel->setText(QCoreApplication::translate("LoanWindow", "Username:  Thanaphat", nullptr));
        BalanceLabel->setText(QCoreApplication::translate("LoanWindow", "Balance:   10,212.00 THB", nullptr));
        BalanceLabel_2->setText(QCoreApplication::translate("LoanWindow", "Loan Balance:   1,010.20 THB", nullptr));
        pushButton->setText(QCoreApplication::translate("LoanWindow", "Withdraw to Balance", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoanWindow: public Ui_LoanWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOANWINDOW_H
