#ifndef NORMALUSER_H
#define NORMALUSER_H
#include "user.h"
#include <QString>
class normaluser:public user
{
private:
    static QString type;
public:
    normaluser();
    normaluser(QString, QString, QDate,QString, QString);
    QString getType()const;
};

#endif // NORMALUSER_H
