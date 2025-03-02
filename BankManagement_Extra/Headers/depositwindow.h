#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QDialog>

namespace Ui {
class DepositWindow;
}

class DepositWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DepositWindow(const QString &username, const QString &accountNumber, double balance, QWidget *parent = nullptr);
    ~DepositWindow();

private slots:
    void handleDeposit();
    void goBack();

private:
    Ui::DepositWindow *ui;
    QString userName;
    QString accNumber;
    double accountBalance;
};

#endif // DEPOSITWINDOW_H
