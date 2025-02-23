/********************************************************************************
** Form generated from reading UI file 'registerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWINDOW_H
#define UI_REGISTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWindow
{
public:
    QLabel *label;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_4;
    QLineEdit *confirmPasswordEdit;
    QLineEdit *passwordEdit;
    QLabel *label_14;
    QLabel *label_9;
    QLabel *label_15;
    QLineEdit *usernameEdit;
    QPushButton *registerButton;
    QPushButton *CancleBtn;

    void setupUi(QDialog *RegisterWindow)
    {
        if (RegisterWindow->objectName().isEmpty())
            RegisterWindow->setObjectName("RegisterWindow");
        RegisterWindow->resize(450, 500);
        label = new QLabel(RegisterWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(140, 20, 171, 41));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        gridLayoutWidget = new QWidget(RegisterWindow);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(60, 60, 331, 251));
        gridLayout_4 = new QGridLayout(gridLayoutWidget);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        confirmPasswordEdit = new QLineEdit(gridLayoutWidget);
        confirmPasswordEdit->setObjectName("confirmPasswordEdit");

        gridLayout_4->addWidget(confirmPasswordEdit, 2, 2, 1, 1);

        passwordEdit = new QLineEdit(gridLayoutWidget);
        passwordEdit->setObjectName("passwordEdit");

        gridLayout_4->addWidget(passwordEdit, 1, 2, 1, 1);

        label_14 = new QLabel(gridLayoutWidget);
        label_14->setObjectName("label_14");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label_14->setFont(font1);

        gridLayout_4->addWidget(label_14, 1, 0, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName("label_9");
        label_9->setFont(font1);

        gridLayout_4->addWidget(label_9, 0, 0, 1, 1);

        label_15 = new QLabel(gridLayoutWidget);
        label_15->setObjectName("label_15");
        label_15->setFont(font1);

        gridLayout_4->addWidget(label_15, 2, 0, 1, 1);

        usernameEdit = new QLineEdit(gridLayoutWidget);
        usernameEdit->setObjectName("usernameEdit");

        gridLayout_4->addWidget(usernameEdit, 0, 2, 1, 1);

        registerButton = new QPushButton(RegisterWindow);
        registerButton->setObjectName("registerButton");
        registerButton->setGeometry(QRect(200, 320, 192, 24));
        QFont font2;
        font2.setBold(true);
        registerButton->setFont(font2);
        CancleBtn = new QPushButton(RegisterWindow);
        CancleBtn->setObjectName("CancleBtn");
        CancleBtn->setGeometry(QRect(331, 463, 101, 21));
        QFont font3;
        font3.setBold(false);
        CancleBtn->setFont(font3);

        retranslateUi(RegisterWindow);

        QMetaObject::connectSlotsByName(RegisterWindow);
    } // setupUi

    void retranslateUi(QDialog *RegisterWindow)
    {
        RegisterWindow->setWindowTitle(QCoreApplication::translate("RegisterWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("RegisterWindow", "Register Window", nullptr));
        label_14->setText(QCoreApplication::translate("RegisterWindow", "Password:", nullptr));
        label_9->setText(QCoreApplication::translate("RegisterWindow", "Username:", nullptr));
        label_15->setText(QCoreApplication::translate("RegisterWindow", "Password \n"
"Confirm:", nullptr));
        registerButton->setText(QCoreApplication::translate("RegisterWindow", "Create Account", nullptr));
        CancleBtn->setText(QCoreApplication::translate("RegisterWindow", "Cancle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWindow: public Ui_RegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWINDOW_H
