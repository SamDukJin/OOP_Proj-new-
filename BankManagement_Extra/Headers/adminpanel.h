#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>

namespace Ui {
class adminpanel;
}

class adminpanel : public QDialog
{
    Q_OBJECT

public:
    explicit adminpanel(QWidget *parent = nullptr);
    ~adminpanel();
    void loadAccounts();

private slots:
    void homebtn();
    void changeaccnum();
    void deleteAccount();
    void deactivateAccount();
    void activateAccount();

private:
    Ui::adminpanel *ui;
};

#endif // ADMINPANEL_H
