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

private slots:
    void homebtn();

private:
    Ui::adminpanel *ui;
};

#endif // ADMINPANEL_H
