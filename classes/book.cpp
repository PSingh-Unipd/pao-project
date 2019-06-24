#include "book.h"

//descrizione dei vari metodo nel file book.h
book::book() {}
book::book(QString c, QString n, QString a, QString i, QDate d, QString ds)
    : cover(c), name(n), author(a), isbn(i), pDate(d), desc(ds) {}
QString book::getAut() const { return author; }
book::~book() {}

QString book::getCover() const { return cover; }
QString book::getName() const { return name; }
QString book::getDesc() const { return desc; }
QString book::getISBN() const { return isbn; }
QDate book::getDate() const { return pDate; }
