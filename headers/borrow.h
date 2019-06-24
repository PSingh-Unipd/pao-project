#ifndef BORROW_H
#define BORROW_H
#include <QString>
#include <QDate>


//un oggetto di questa classe rapressenta un prestito
class borrow
{
private:
    QString bookID;//ISBN LIBRO
    QString bookName;//NOME LIBRO
    QDate sdate;//DATA INIZIO
    QDate eDate;//DATA FINE
    QString userID; //NOME UTENTE
public:
    borrow();
    borrow(QString, QString,QDate, QDate, QString);
    QDate getSDATE()const;
    QDate getEDATE()const;
    QString getBookID()const;
    QString getBookName()const;
    QString getUser()const;
};

#endif // BORROW_H
