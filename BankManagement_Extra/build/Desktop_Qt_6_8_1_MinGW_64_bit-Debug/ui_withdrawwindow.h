/********************************************************************************
** Form generated from reading UI file 'withdrawwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WITHDRAWWINDOW_H
#define UI_WITHDRAWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_WithdrawWindow
{
public:

    void setupUi(QDialog *WithdrawWindow)
    {
        if (WithdrawWindow->objectName().isEmpty())
            WithdrawWindow->setObjectName("WithdrawWindow");
        WithdrawWindow->resize(400, 300);

        retranslateUi(WithdrawWindow);

        QMetaObject::connectSlotsByName(WithdrawWindow);
    } // setupUi

    void retranslateUi(QDialog *WithdrawWindow)
    {
        WithdrawWindow->setWindowTitle(QCoreApplication::translate("WithdrawWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WithdrawWindow: public Ui_WithdrawWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WITHDRAWWINDOW_H
