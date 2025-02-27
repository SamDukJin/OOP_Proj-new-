#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWindow(const QString &name = "", const QString &password = "",const QString &accountnumber="", QWidget *parent = nullptr);
    ~SettingWindow();

private slots:
    void changeUsrNam();
    void changePswd();
    void delAcc();
    void logout();
    void gohome();
    void clearConfirmPlaceholder();
private:
    Ui::SettingWindow *ui;
    QString userName;
    QString Password;
    QString accountNumber;
};

#endif // SETTINGWINDOW_H
