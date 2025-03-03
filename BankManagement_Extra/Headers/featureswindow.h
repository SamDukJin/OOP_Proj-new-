#ifndef FEATURESWINDOW_H
#define FEATURESWINDOW_H

#include <QDialog>

namespace Ui {
class FeaturesWindow;
}

class FeaturesWindow : public QDialog {
    Q_OBJECT

public:
    explicit FeaturesWindow(const QString &name = "", const QString &accountNum = "", double balance = 0.0, QWidget *parent = nullptr);
    ~FeaturesWindow();

private slots:
    void goHomeBtn();
    void goDeposit();
    void goWithdraw();
    void goTransfer();
private:
    Ui::FeaturesWindow *ui;

    QString userName;
    QString accountNumber;
    double accountBalance;
};

#endif // FEATURESWINDOW_H
