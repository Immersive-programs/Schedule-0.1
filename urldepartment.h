#ifndef URLDEPARTMENT_H
#define URLDEPARTMENT_H

#include <QObject>

class urldepartment: public QObject
{
    Q_OBJECT

public:
    explicit urldepartment(QObject *parent = 0);

    QString getURL(const int num);
};

#endif // URLDEPARTMENT_H
