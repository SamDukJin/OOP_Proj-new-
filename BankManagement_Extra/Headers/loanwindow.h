#ifndef LOANWINDOW_H
#define LOANWINDOW_H

#include <QDialog>
namespace Ui {
class LoanWindow;
}

class LoanWindow : public QDialog {
    Q_OBJECT

public:
    explicit LoanWindow(const QString &name, const QString &accountNum, double balance, QWidget *parent = nullptr);
    ~LoanWindow();

private slots:
    void takeLoan();
    void fetchLoanDetails();
    void homebtn();
    void updateUI();
    void updateDatabase(double loanAmount);
    void payloan();

private:
    Ui::LoanWindow *ui;
    QString userName;
    QString accountNumber;
    double accountBalance;
    double totalLoan = 0.0;
};

#endif // LOANWINDOW_H
