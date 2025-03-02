#ifndef SHOWRECWINDOW_H
#define SHOWRECWINDOW_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class ShowRecWindow;
}

class ShowRecWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ShowRecWindow(const QString &name, const QString &accountNum, double balance, QWidget *parent = nullptr);
    ~ShowRecWindow();

private slots:
    void homebtn();

private:
    Ui::ShowRecWindow *ui;
    QString userName;
    QString accountNumber;
    double accountBalance;
    QSqlTableModel *model=nullptr;

    void loadTransactionHistory();
};

#endif // SHOWRECWINDOW_H
