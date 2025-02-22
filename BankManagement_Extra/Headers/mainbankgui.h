#ifndef MAINBANKGUI_H
#define MAINBANKGUI_H

#include <QDialog>

namespace Ui {
class MainBankGUI;
}

class MainBankGUI : public QDialog {
    Q_OBJECT

public:
    explicit MainBankGUI(const QString &username, const QString &accountNumber, double accountBalance, QWidget *parent = nullptr);
    ~MainBankGUI();


private:
    Ui::MainBankGUI *ui;

    QString userName;
    QString accountNumber;
    double accountBalance;

    void fetchUserDetails(const QString &username);

private slots:
    void openFeaturesWindow();
};

#endif // MAINBANKGUI_H
