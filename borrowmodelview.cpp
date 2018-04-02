#include "borrowmodelview.h"
#include <QMessageBox>
borrowModelView::borrowModelView()
{}

/***METODI VITUALI DERIVATI DALLA SUPER CLASSE***/

//IL METODO RESTITUISCE IL NUMERO DI RIGHE DELLA TABELLA
int borrowModelView::rowCount(const QModelIndex& parent) const
{
  return v.size();
}

//METODO RESTITUISCE IL NUMERO DI COLONNE DELLA TABELLA
int borrowModelView::columnCount(const QModelIndex& parent) const
{
  return 5;
}

//METODO SERVE PER CARICARE DATI NEL MODELLO(TABELLA IN QUESTO CASO)
QVariant borrowModelView::data(const QModelIndex& index, int role) const
{
    int row=index.row();//righe
    int col=index.column();//colonne
    if(role == Qt::DisplayRole)
    {
            borrow *c=v.operator [](row);//carico un prestito base alla riga, ovviamente la riga non superaara mai la dimenzione del vettore v
            if(col==0)
                return c->getBookID();//se è la prima colonna restituisco isbn
            if(col==1)
                return c->getBookName();//seconda colonna nome libro
            if(col==2)
                return c->getSDATE();//data inizio prestito
            if(col==3)
                return c->getEDATE();//data fine prestito
            if(col==4)
                return c->getUser();//data fine prestito

    }
    return QVariant::Invalid;

}

//SERVE PER HEADER DELLA TABELLA(OVVERO I NOME DELLE VARIE COLONNE). IN QUESTO CASO 4 COLONNE
QVariant borrowModelView::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("IBSN");
            case 1:
                return QString("TITOLO");
            case 2:
                return QString("INIZIO PRESTITTO");
            case 3:
                return QString("FINE PRESTITO");
            case 4:
                return QString("UTENTE");
            }
        }
    }
    return QVariant();
}


 bool borrowModelView::addBorrow(QString u, QString is, QString ti, QDate sd, QDate ed){
     beginInsertRows( QModelIndex(),this->rowCount(QModelIndex())-1, this->rowCount(QModelIndex())-1); //notify views and proxy models that a line will be inserted
          v.push_back(new borrow( is, ti, sd, ed, u));
     endInsertRows();
     return true;
 }
bool borrowModelView::removeBorrow(QString user, QString book){
    bool cond=false;
    int row=0;
    for(unsigned int i=0; i<v.size() && !cond; i++){

        borrow* temp=v.operator [](i);
        if(temp->getBookID()==book && temp->getUser()==user){

            cond=true;
        }else{
            row++;
        }
    }

    beginRemoveRows(QModelIndex(), row, row );
        v.erase(v.begin()+row);
    endRemoveRows();
    if(cond){
        return true;
    }
    return false;
}



//METODI PER CARICARE I DATI DAI FILE XML
//RICEVE UN QFILE E UNA STRINGA(nome utente), CARICA TUTTI I PRESTTI DI QUEL UTENTE DAL FILE XML.
void borrowModelView::loadUserBorrow(QFile& f){
    if(!f.open(QFile::Text|QFile::ReadOnly)){
          QMessageBox err;
          err.critical(0,"Opning", "File xml does not found!");
     }else{
          QXmlStreamReader file(&f);
          if (file.readNextStartElement()) {
                   if (file.name() == "borrows"){
                       while(file.readNextStartElement()){
                           if(file.name() == "borrow"){
                               this->loadSingleBorrow(file);
                           }
                           else{
                               file.skipCurrentElement();
                           }
                       }
                   }
                   else{
                       QMessageBox err2;
                       err2.critical(0, "Wrong file","File xml is not a valid file. Please try with another file!");
                   }
               }
          file.clear();
          f.close();
    }
}

void borrowModelView::loadSingleBorrow(QXmlStreamReader &file){
    QString bid, bn,  y, m , d, user;
    QDate sd, ed;
    bool cond=false;
    while(file.readNextStartElement() && !cond){
        if(file.name() == "user"){
                 user = file.readElementText();
         }
        if(file.name() == "isbn"){
                bid = file.readElementText();
         }
        if(file.name() == "title"){
                 bn = file.readElementText();
         }
         if(file.name()=="start_date"){
             while (file.readNextStartElement()) {
                 if(file.name() == "year"){
                         y = file.readElementText();
                 }
                 if(file.name() == "month"){
                         m = file.readElementText();
                 }
                 if(file.name() == "day"){
                         d = file.readElementText();
                  }
                 sd.setDate(y.toInt(), m.toInt(), d.toInt());
             }
         }
         if(file.name()=="end_date"){
             while (file.readNextStartElement()) {
                 if(file.name() == "year"){
                         y = file.readElementText();
                 }
                 if(file.name() == "month"){
                         m = file.readElementText();
                 }
                 if(file.name() == "day"){
                         d = file.readElementText();
                         cond=true;
                  }
                   ed.setDate(y.toInt(), m.toInt(), d.toInt());
             }
         }


     }if(cond){
        v.push_back(new borrow(bid, bn,sd, ed, user));
    }
}


//METODO PER AGGIORNARE IL FILE XML

bool borrowModelView::saveData(QFile& file)const
{
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox err;
            err.critical(0," Errore apertura", "Nessun file XML trovato!");
            return false;
        }
            QXmlStreamWriter *writer = new QXmlStreamWriter();
            writer->setDevice(&file);
            writer->writeStartDocument();
            writer->writeStartElement("borrows");

            for (unsigned int i=0; i < v.size() ; i++)
            {
                borrow *b = v.operator [](i);
                    writer->writeStartElement("borrow");
                    writer->writeTextElement("user", b->getUser());
                    writer->writeTextElement("isbn",b->getBookID());
                    writer->writeTextElement("title",b->getBookName());
                    writer->writeStartElement("start_date");
                        writer->writeTextElement("year",QString::number(b->getSDATE().year()));
                        writer->writeTextElement("month",QString::number(b->getSDATE().month()));
                        writer->writeTextElement("day", QString::number(b->getSDATE().day()));
                    writer->writeEndElement();
                    writer->writeStartElement("end_date");
                        writer->writeTextElement("year",QString::number(b->getEDATE().year()));
                        writer->writeTextElement("month",QString::number(b->getEDATE().month()));
                        writer->writeTextElement("day", QString::number(b->getEDATE().day()));
                    writer->writeEndElement();
                    writer->writeEndElement();
            }
            writer->writeEndElement();
            writer->writeEndDocument();
            delete writer;
            return true;
}









