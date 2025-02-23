#ifndef REGISTERWIN_H
#define REGISTERWIN_H

#include <QDialog>

namespace Ui {
class RegisterWin;
}

class RegisterWin : public QDialog {
    Q_OBJECT

public:
    explicit RegisterWin(QWidget *parent = nullptr);
    ~RegisterWin();

private slots:
    void validateInputs();
    void handleRegistration();

private:
    Ui::RegisterWin *ui;
    QString generateAccountNumber();
};

#endif // REGISTERWIN_H
