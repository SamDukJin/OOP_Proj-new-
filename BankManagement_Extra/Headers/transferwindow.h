#ifndef TRANSFERWINDOW_H
#define TRANSFERWINDOW_H

#include <QDialog>

namespace Ui {
class transferwindow;
}

class transferwindow : public QDialog
{
    Q_OBJECT

public:
    explicit transferwindow(const QString &username, const QString &accountNumber, double balance, QWidget *parent=nullptr);
    ~transferwindow();

private slots:
    void homebtn();
    void checkAccountAvailability();
    void processTransfer();

private:
    Ui::transferwindow *ui;

    QString userName;
    QString accountNum;
    double balance;
};

#endif // TRANSFERWINDOW_H
