#include "programmigbook.h"

programmigbook::programmigbook()
{
}
programmigbook::programmigbook(QString c, QString n, QString a, QString is, QDate d, QString ds, QString l)
    : book(c, n, a, is, d, ds), pLang(l) {}
programmigbook *programmigbook::clone() const { return new programmigbook(*this); }
QString programmigbook::getSubject() const { return pLang; }
