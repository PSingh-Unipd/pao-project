#ifndef BORROWMODELVIEW_H
#define BORROWMODELVIEW_H
#include <QAbstractTableModel>
#include <vector>
#include <QFile>
#include <QDate>
#include <QXmlStreamReader>
#include <borrow.h>

class borrowModelView:public QAbstractTableModel
{
private:
    std::vector<borrow*> v;
public:
    borrowModelView();

    //IMPLEMENTAZIONE DEI METODI VITUALI PURI DELLA SUPER CLASSE QAbstractTableModel -SOLO LETTURA-
    int rowCount(const QModelIndex& parent) const; //restituisce il numero di righe della tabella
    int columnCount(const QModelIndex& parent) const; //numero di colonne
    QVariant data(const QModelIndex& index, int role) const; //serve per "popolare" la tabella
    QVariant headerData(int, Qt::Orientation , int ) const; //per "setare" i nomi delle colonne(guardare il file .cpp)

    //METODO per inserire/rimuovere un (nuovo) prestito
    bool addBorrow(QString, QString, QString, QDate, QDate);//sicuramente c'era un modo migliore per implementare l'inserimento di un nuovo libro
    bool removeBorrow(QString, QString);//rimuove un libro dal contenitore e segnale a tute le views della rimozione


    //METODI PER CARICARE DATI DAL FILE XML NEL CONTENITORE
    void loadUserBorrow(QFile&); //fa la stessa cosa solo che in questo caso i libri caricati sono di uno specidifico utente.Infatti riceve come campo dati una stringa contenente id(codice fiscale) di uno specifico utente
    void loadSingleBorrow(QXmlStreamReader&);//carica un singlo libro..usata per le due funzioni sopra

    //METODO PER AGGIORNARE IL FILE XML(DATABASE)
    bool saveData(QFile &)const;
};

#endif // BORROWMODELVIEW_H
