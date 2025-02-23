#ifndef LOANWINDOW_H
#define LOANWINDOW_H

#include <QDialog>

namespace Ui {
class LoanWindow;
}

class LoanWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoanWindow(QWidget *parent = nullptr);
    ~LoanWindow();

private:
    Ui::LoanWindow *ui;
};

#endif // LOANWINDOW_H
