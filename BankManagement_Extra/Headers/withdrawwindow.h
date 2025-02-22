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
    explicit WithdrawWindow(QWidget *parent = nullptr);
    ~WithdrawWindow();

private:
    Ui::WithdrawWindow *ui;
};

#endif // WITHDRAWWINDOW_H
