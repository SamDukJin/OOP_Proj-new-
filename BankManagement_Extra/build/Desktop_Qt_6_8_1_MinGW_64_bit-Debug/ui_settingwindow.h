/********************************************************************************
** Form generated from reading UI file 'settingwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWINDOW_H
#define UI_SETTINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingWindow
{
public:
    QLabel *label;
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *SettingWindow)
    {
        if (SettingWindow->objectName().isEmpty())
            SettingWindow->setObjectName("SettingWindow");
        SettingWindow->resize(600, 500);
        label = new QLabel(SettingWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 251, 61));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        tableWidget = new QTableWidget(SettingWindow);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignJustify|Qt::AlignBottom);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(120, 70, 351, 91));
        QFont font1;
        font1.setBold(true);
        tableWidget->setFont(font1);
        pushButton = new QPushButton(SettingWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(380, 370, 91, 51));
        pushButton_2 = new QPushButton(SettingWindow);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(230, 190, 121, 31));
        label_2 = new QLabel(SettingWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 180, 101, 51));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        label_2->setFont(font2);
        pushButton_3 = new QPushButton(SettingWindow);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(260, 370, 91, 51));

        retranslateUi(SettingWindow);

        QMetaObject::connectSlotsByName(SettingWindow);
    } // setupUi

    void retranslateUi(QDialog *SettingWindow)
    {
        SettingWindow->setWindowTitle(QCoreApplication::translate("SettingWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SettingWindow", "Account Setting Window", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SettingWindow", "Username:", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SettingWindow", "Account Number:", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SettingWindow", "Account Properties:", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(0, 0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SettingWindow", "Thanaphat", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SettingWindow", "1110-01023-4122", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton->setText(QCoreApplication::translate("SettingWindow", "Logout", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SettingWindow", "Change Password", nullptr));
        label_2->setText(QCoreApplication::translate("SettingWindow", "Password:", nullptr));
        pushButton_3->setText(QCoreApplication::translate("SettingWindow", "Delete Account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingWindow: public Ui_SettingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWINDOW_H
