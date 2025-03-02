#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QLocale>

inline QString formatBalance(double amount) {
    QLocale locale(QLocale::English);
    return locale.toString(amount, 'f', 2) + " ฿";
}
#endif // UTILS_H
