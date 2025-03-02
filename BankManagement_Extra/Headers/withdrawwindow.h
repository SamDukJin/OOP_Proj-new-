#ifndef WITHDRAWWINDOW_H
#define WITHDRAWWINDOW_H

#include <QDialog>

namespace Ui {
class WithdrawWindow;
}

class WithdrawWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawWindow(const QString &username, const QString &accountNumber, double balance, QWidget *parent = nullptr);
    ~WithdrawWindow();

private slots:
    void handleWithdraw();
    void goBack();

private:
    Ui::WithdrawWindow *ui;
    QString userName;
    QString accNumber;
    double accountBalance;

};

#endif // WITHDRAWWINDOW_H
