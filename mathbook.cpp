#include "mathbook.h"


mathbook::mathbook(){}
mathbook::mathbook(QString c, QString n, QString a, QString is,  QDate d, QString ds, QString sj)
    :book(c, n,a,is,d,ds),subject(sj){}
mathbook* mathbook::clone()const{ return new mathbook(*this); }
QString mathbook::getSubject()const{return subject;}

