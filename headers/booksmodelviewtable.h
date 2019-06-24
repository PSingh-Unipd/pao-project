#ifndef BOOKSMODELVIEWTABLE_H
#define BOOKSMODELVIEWTABLE_H
#include <QAbstractTableModel>
#include "bookscontainer.h"
#include <QString>
#include <QFile>
#include "book.h"
#include "programmigbook.h"
#include "mathbook.h"
#include "QMessageBox"

/***CLASSE IMPLEMENTATA PER IL MODEL-VIEW TECNIQUE***/

class booksModelViewTable : public QAbstractTableModel
{
public:
    booksModelViewTable(); //costruttore senza parametri
    //METEDO AGGIUNTO PER FORNIRE LA COPERTINA ALLE VIEWS(se serve)
    QString getCover(const QString) const; //poiche non stampo nella tabella quindi il modello non lo contiene fornisco questo metodo ai "views" per avere la copertina dato un ISBN del libro che è univoco!

    //IMPLEMENTAZIONE DEI METODI VITUALI PURI DELLA SUPER CLASSE QAbstractTableModel
    int rowCount(const QModelIndex &parent) const;           //restituisce il numero di righe della tabella
    int columnCount(const QModelIndex &parent) const;        //numero di colonne
    QVariant data(const QModelIndex &index, int role) const; //serve per "popolare" la tabella
    QVariant headerData(int, Qt::Orientation, int) const;    //per "setare" i nomi delle colonne(guardare il file .cpp)

    //METODO per inserire/rimuovere un (nuovo) libro
    bool addBook(QString t, QString is, QString c, QString n, QString au, QString d, QString s, QDate pd); //sicuramente c'era un modo migliore per implementare l'inserimento di un nuovo libro
    bool removeBook(QString &);                                                                            //rimuove un libro dal contenitore e segnale a tute le views della rimozione

    //METODI PER CARICARE DATI DAL FILE XML NEL CONTENITORE
    void setModelContainer(QFile &);         //Prende come argomento un QFile(in questo caso un file xml)e riempe il contenitore con i libri presenti nel file.
    void loadSingleBook(QXmlStreamReader &); //carica un singlo libro...utilizzato per implementare il metodo sopra(forse era meglio farlo statico?)

    //METODO PER AGGIORNARE IL FILE XML(DATABASE)
    bool saveData(QFile &) const;

    //METODI PER RIMUOVER E AGGIUNGER UNA COPIA SOLA
    void addCopy(QString);
    void removeCopy(QString);

private:
    bookscontainer a; //contenitore che contiene tutti i libri caricati dal file xml
};

#endif // BOOKSMODELVIEWTABLE_H
