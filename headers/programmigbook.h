#ifndef PROGRAMMIGBOOK_H
#define PROGRAMMIGBOOK_H
#include"book.h"
#include<QString>
#include<QDate>
class programmigbook: public book
{
private:
    QString pLang;
public:
    programmigbook();
    programmigbook(QString, QString, QString, QString, QDate,QString,  QString);
    programmigbook* clone()const;
    QString getSubject()const;

};

#endif // PROGRAMMIGBOOK_H
