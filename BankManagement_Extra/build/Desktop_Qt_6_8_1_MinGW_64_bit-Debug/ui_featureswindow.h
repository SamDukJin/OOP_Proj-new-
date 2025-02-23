/********************************************************************************
** Form generated from reading UI file 'featureswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FEATURESWINDOW_H
#define UI_FEATURESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FeaturesWindow
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *BalanceLabel;
    QLabel *AccNumLabel;
    QLabel *UsernamLabel;

    void setupUi(QDialog *FeaturesWindow)
    {
        if (FeaturesWindow->objectName().isEmpty())
            FeaturesWindow->setObjectName("FeaturesWindow");
        FeaturesWindow->resize(700, 500);
        label = new QLabel(FeaturesWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(250, 0, 201, 50));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        label->setFont(font);
        pushButton = new QPushButton(FeaturesWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(130, 310, 121, 71));
        pushButton_2 = new QPushButton(FeaturesWindow);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(290, 310, 111, 71));
        pushButton_3 = new QPushButton(FeaturesWindow);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(440, 310, 111, 71));
        BalanceLabel = new QLabel(FeaturesWindow);
        BalanceLabel->setObjectName("BalanceLabel");
        BalanceLabel->setGeometry(QRect(30, 140, 481, 21));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        BalanceLabel->setFont(font1);
        BalanceLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        AccNumLabel = new QLabel(FeaturesWindow);
        AccNumLabel->setObjectName("AccNumLabel");
        AccNumLabel->setGeometry(QRect(30, 80, 481, 21));
        AccNumLabel->setFont(font1);
        AccNumLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));
        UsernamLabel = new QLabel(FeaturesWindow);
        UsernamLabel->setObjectName("UsernamLabel");
        UsernamLabel->setGeometry(QRect(30, 110, 481, 21));
        UsernamLabel->setFont(font1);
        UsernamLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}"));

        retranslateUi(FeaturesWindow);

        QMetaObject::connectSlotsByName(FeaturesWindow);
    } // setupUi

    void retranslateUi(QDialog *FeaturesWindow)
    {
        FeaturesWindow->setWindowTitle(QCoreApplication::translate("FeaturesWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FeaturesWindow", "Features Window", nullptr));
        pushButton->setText(QCoreApplication::translate("FeaturesWindow", "Withdraw", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FeaturesWindow", "Deposit", nullptr));
        pushButton_3->setText(QCoreApplication::translate("FeaturesWindow", "Transfer", nullptr));
        BalanceLabel->setText(QCoreApplication::translate("FeaturesWindow", "Balance:   10,212.00 THB", nullptr));
        AccNumLabel->setText(QCoreApplication::translate("FeaturesWindow", "Account Number: 1110-01023-4122", nullptr));
        UsernamLabel->setText(QCoreApplication::translate("FeaturesWindow", "Username:  Thanaphat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FeaturesWindow: public Ui_FeaturesWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEATURESWINDOW_H
