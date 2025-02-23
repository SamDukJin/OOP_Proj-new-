/********************************************************************************
** Form generated from reading UI file 'loginwin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIN_H
#define UI_LOGINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_LoginWin
{
public:

    void setupUi(QDialog *LoginWin)
    {
        if (LoginWin->objectName().isEmpty())
            LoginWin->setObjectName("LoginWin");
        LoginWin->resize(450, 500);

        retranslateUi(LoginWin);

        QMetaObject::connectSlotsByName(LoginWin);
    } // setupUi

    void retranslateUi(QDialog *LoginWin)
    {
        LoginWin->setWindowTitle(QCoreApplication::translate("LoginWin", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWin: public Ui_LoginWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIN_H
