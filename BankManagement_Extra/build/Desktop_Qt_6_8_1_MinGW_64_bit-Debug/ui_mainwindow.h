/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *Usnam_inp;
    QLineEdit *Pswrd_inp;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_4;
    QPushButton *LoginBtn;
    QLabel *label;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_5;
    QPushButton *RegisterBtn_2;
    QLabel *label_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(450, 500);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(49, 49, 351, 141));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName("label_6");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_6->setFont(font);

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");
        label_7->setFont(font);

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        Usnam_inp = new QLineEdit(gridLayoutWidget);
        Usnam_inp->setObjectName("Usnam_inp");

        gridLayout_3->addWidget(Usnam_inp, 0, 1, 1, 1);

        Pswrd_inp = new QLineEdit(gridLayoutWidget);
        Pswrd_inp->setObjectName("Pswrd_inp");

        gridLayout_3->addWidget(Pswrd_inp, 1, 1, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(50, 190, 351, 41));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        LoginBtn = new QPushButton(gridLayoutWidget_2);
        LoginBtn->setObjectName("LoginBtn");

        gridLayout_4->addWidget(LoginBtn, 0, 0, 1, 1, Qt::AlignmentFlag::AlignVCenter);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(150, 10, 151, 31));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        label->setFont(font1);
        gridLayoutWidget_3 = new QWidget(centralwidget);
        gridLayoutWidget_3->setObjectName("gridLayoutWidget_3");
        gridLayoutWidget_3->setGeometry(QRect(50, 230, 351, 53));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        RegisterBtn_2 = new QPushButton(gridLayoutWidget_3);
        RegisterBtn_2->setObjectName("RegisterBtn_2");

        gridLayout_5->addWidget(RegisterBtn_2, 1, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_3);
        label_5->setObjectName("label_5");
        label_5->setFont(font);

        gridLayout_5->addWidget(label_5, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        LoginBtn->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Login System...", nullptr));
        RegisterBtn_2->setText(QCoreApplication::translate("MainWindow", "Register Now!", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "               Did not have an account yet? ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
