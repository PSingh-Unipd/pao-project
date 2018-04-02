#include "borrow.h"

borrow::borrow()
{}

borrow::borrow(QString is, QString bn,QDate s, QDate e, QString u )
    : bookID(is), bookName(bn), sdate(s), eDate(e), userID(u){
}
QString borrow::getBookID()const{return bookID;}
QString borrow::getBookName()const{return bookName;}
QDate borrow::getEDATE()const{return eDate;}
QDate borrow::getSDATE()const{return sdate;}
QString borrow::getUser()const{return userID;}
