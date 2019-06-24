#ifndef MATHBOOK_H
#define MATHBOOK_H
#include "book.h"
#include <QString>
#include <QDate>

class mathbook : public book
{
private:
    static QString type;
    QString subject;
public:
    mathbook();
    mathbook(QString, QString, QString, QString, QDate, QString, QString);
    QString getSubject()const;
    mathbook* clone()const;
};

#endif // MATHBOOK_H

