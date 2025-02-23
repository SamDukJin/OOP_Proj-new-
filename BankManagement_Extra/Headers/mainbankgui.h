#ifndef MAINBANKGUI_H
#define MAINBANKGUI_H

#include <QDialog>

namespace Ui {
class MainBankGUI;
}

class MainBankGUI : public QDialog {
    Q_OBJECT

public:
    explicit MainBankGUI(const QString &name = "", const QString &accountNum = "", double balance = 0.0, QWidget *parent = nullptr);
    ~MainBankGUI();


private:
    Ui::MainBankGUI *ui;

    QString userName;
    QString accountNumber;
    double accountBalance;

    void fetchUserDetails(const QString &username);

private slots:
    void openFeaturesWindow();
    void openAdminPanel();
};

#endif // MAINBANKGUI_H
