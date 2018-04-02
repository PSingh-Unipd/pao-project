#ifndef BOOK_H
#define BOOK_H
#include <QDate>
#include <QString>
#include <QPixmap>
class book
{
private:
    QString cover;//immagine di copertina
    QString name;//nome
    QString author;//scrittore/i
    QString isbn;//codice che identifica il libro univocamente
    QDate pDate;//data pubblicazione
    QString desc;//descrizione
public:
    book();
    book(QString, QString, QString, QString, QDate, QString);
    QString getCover()const;
    QString getName()const;//restituisce il nome del libro
    QString getAut()const;//scrittore
    QString getDesc()const;//la descrizione
    QDate getDate()const;//la data
    QString getISBN()const;// restituisce il ISBN del
    virtual QString getSubject()const=0;
    virtual book* clone()const=0;//metodo per la clonazione
    virtual ~book();//distruttore virtuale
};

#endif // BOOK_H
