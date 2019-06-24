#include "booksmodelviewtable.h"
#include "string.h"
#include "book.h"
#include <QPixmap>
#include "programmigbook.h"
#include "mathbook.h"
#include "QMessageBox"
#include <QDebug>
#include <QDate>
#include <QFileDialog>

/****IMPLEMENTAZIONE DEI METODI DELLA CLASSE(booksmodelvietable) MODELLO PER I DATI DI TIPO LIBRI****/

//COSTRUTORE SENZA PRAMETRI
booksModelViewTable::booksModelViewTable()
{
}

//SERVE PER LA COPERTINA, VISTO CHE IN TABELLA E NEL MODELLO NON VIENE CARICATA!
QString booksModelViewTable::getCover(const QString t) const
{
    bookscontainer::iterator it = a.begin();
    for (; it != a.end(); it++)
    {
        book *temp = a.operator[](it);
        if (temp->getISBN() == t)
        {
            return temp->getCover();
        }
    }
    return "";
}

//IL METODO RESTITUISCE IL NUMERO DI RIGHE DELLA TABELLA
int booksModelViewTable::rowCount(const QModelIndex &parent) const
{
    return a.size();
}

//METODO RESTITUISCE IL NUMERO DI COLONNE DELLA TABELLA
int booksModelViewTable::columnCount(const QModelIndex &parent) const
{
    return 7;
}

/***METODI VITUALI DERIVATI DALLA SUPER CLASSE***/

//METODO SERVE PER CARICARE DATI NEL MODELLO(TABELLA IN QUESTO CASO)
QVariant booksModelViewTable::data(const QModelIndex &index, int role) const
{
    int row = index.row();       //righe
    int col = index.column();    //colonne
    book *c = a.operator[](row); //"pesco" il singolo libro dal contenitore(a) e lo faccio puntatre da c
    if (role == Qt::DisplayRole)
    {
        if (col == 0)
            return c->getISBN();
        if (col == 1) //controllo vari casi, base alla colonna della tabella carico l 'informazione nel modello
            return c->getName();
        if (col == 2)
            return c->getAut();
        if (col == 3)
            return c->getDate();
        if (col == 4)
            return c->getSubject();
        if (col == 5)
            return c->getDesc();
        if (col == 6)
            return a.getCN(a.operator[](row));
    }
    return QVariant::Invalid;
}

//SERVE PER HEADER DELLA TABELLA(OVVERO I NOME DELLE VARIE COLONNE)
QVariant booksModelViewTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("IBSN");
            case 1:
                return QString("NOME");
            case 2:
                return QString("AUTORE");
            case 3:
                return QString("DATA PUB.");
            case 4:
                return QString("ARGOMENTO");
            case 5:
                return QString("DESCRIZIONE");
            case 6:
                return QString("COPIE DISPONIBILI");
            }
        }
    }
    return QVariant();
}

bool booksModelViewTable::addBook(QString t, QString is, QString c, QString n, QString au, QString d, QString s, QDate pd)
{
    bool cond = false;
    for (unsigned int i = 0; i < a.size() && !cond; i++)
    {
        book *temp = a.operator[](i);
        if (temp->getISBN() == is)
        {
            cond = true;
            a.addBook(temp, 1);
            emit dataChanged(QModelIndex(), QModelIndex());
            return true;
        }
    }
    if (!cond)
    {
        if (t == "Libro di Programmazione")
        {
            beginInsertRows(QModelIndex(), this->rowCount(QModelIndex()) - 1, this->rowCount(QModelIndex()) - 1); //notify views and proxy models that a line will be inserted
            a.addBook(new programmigbook(c, n, au, is, pd, d, s), 1);
            endInsertRows();
            return true;
        }
        if (t == "Libro di Matematica")
        {
            beginInsertRows(QModelIndex(), this->rowCount(QModelIndex()) - 1, this->rowCount(QModelIndex()) - 1); //notify views and proxy models that a line will be inserted
            a.addBook(new mathbook(c, n, au, is, pd, d, s), 1);
            endInsertRows();
            return true;
        }
    }
    return false;
}

bool booksModelViewTable::removeBook(QString &is)
{ //Sicuramente c'era un modo piu elegante per eliminare un libro
    bool cond = false;
    int row;
    for (unsigned int i = 0; i < a.size() && !cond; i++)
    {
        row = i;
        book *temp = a.operator[](i);
        if (temp->getISBN() == is)
        {
            cond = true;
        }
    }
    beginRemoveRows(QModelIndex(), row, row);
    cond = a.removeAllCopies(is);
    endRemoveRows();
    if (cond)
    {
        return true;
    }
    return false;
}

//METODI PER LA SINGOLA COPIA
void booksModelViewTable::addCopy(QString is)
{
    for (unsigned int i = 0; i < a.size(); i++)
    {
        book *temp = a.operator[](i);
        if (temp->getISBN() == is)
        {
            a.incCN(temp);
            return;
        }
    }
}
void booksModelViewTable::removeCopy(QString is)
{
    for (unsigned int i = 0; i < a.size(); i++)
    {
        book *temp = a.operator[](i);
        if (temp->getISBN() == is)
        {
            a.decCN(temp);
            return;
        }
    }
}

//METODI PER CARICARE I DATI DAI FILE XML
void booksModelViewTable::setModelContainer(QFile &f)
{

    if (!f.open(QFile::Text | QFile::ReadOnly))
    {
        QMessageBox err;
        err.critical(0, " Errore apertura", "Nessun file XML trovato!");
    }
    else
    {
        QXmlStreamReader file(&f);
        if (file.readNextStartElement())
        {
            if (file.name() == "books")
            {
                while (file.readNextStartElement())
                {
                    if (file.name() == "book")
                    {
                        this->loadSingleBook(file);
                    }
                    else
                    {
                        file.skipCurrentElement();
                    }
                }
            }
            else
            {
                QMessageBox err2;
                err2.critical(0, "Errore File!", "Il file selezionato non è un file xml valido!");
            }
        }
        file.clear();
        f.close();
    }
}

void booksModelViewTable::loadSingleBook(QXmlStreamReader &file)
{
    QString name, cover, author, isbn, desc, sub, type, y, m, d;
    bool cond = false;
    int nc = 1;
    type = file.attributes().value("type").toString();
    while (file.readNextStartElement() && !cond)
    {
        if (file.name() == "cover")
        {
            cover = file.readElementText();
        }
        if (file.name() == "isbn")
        {
            isbn = file.readElementText();
        }
        if (file.name() == "title")
        {
            name = file.readElementText();
        }
        if (file.name() == "author")
        {
            author = file.readElementText();
        }
        if (file.name() == "publish_date")
        {
            while (file.readNextStartElement())
            {
                if (file.name() == "year")
                {
                    y = file.readElementText();
                }
                if (file.name() == "month")
                {
                    m = file.readElementText();
                }
                if (file.name() == "day")
                {
                    d = file.readElementText();
                }
            }
        }
        if (file.name() == "description")
        {
            desc = file.readElementText();
        }
        if (file.name() == "sub")
        {
            sub = file.readElementText();
        }
        if (file.name() == "numberC")
        {
            nc = file.readElementText().toInt();
            cond = true;
        }
    }
    QDate p(y.toInt(), m.toInt(), d.toInt());

    if (type == "programming")
    {

        a.addBook(new programmigbook(cover, name, author, isbn, p, desc, sub), nc);
    }
    if (type == "math")
    {
        a.addBook(new mathbook(cover, name, author, isbn, p, desc, sub), nc);
    }
}

//METODO PER AGGIORNARE IL FILE XML

bool booksModelViewTable::saveData(QFile &file) const
{
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox err;
        err.critical(0, " Errore apertura", "Nessun file XML trovato!");
        return false;
    }
    QXmlStreamWriter *writer = new QXmlStreamWriter();
    writer->setDevice(&file);
    writer->writeStartDocument();
    writer->writeStartElement("books");
    for (unsigned int i = 0; i < a.size(); i++)
    {
        QString type;
        book *b = dynamic_cast<programmigbook *>(a.operator[](i));
        if (b)
        {
            type = "programming";
        }
        else
        {
            b = dynamic_cast<mathbook *>(a.operator[](i));
            type = "math";
        }
        writer->writeStartElement("book");
        writer->writeAttribute("type", type);
        writer->writeTextElement("cover", b->getCover());
        writer->writeTextElement("isbn", b->getISBN());
        writer->writeTextElement("title", b->getName());
        writer->writeTextElement("author", b->getAut());
        writer->writeStartElement("publish_date");
        writer->writeTextElement("year", QString::number(b->getDate().year()));
        writer->writeTextElement("month", QString::number(b->getDate().month()));
        writer->writeTextElement("day", QString::number(b->getDate().day()));
        writer->writeEndElement();
        writer->writeTextElement("description", b->getDesc());
        writer->writeTextElement("sub", b->getSubject());
        writer->writeTextElement("numberC", QString::number(a.getCN(b)));
        writer->writeEndElement();
    }
    writer->writeEndElement();
    writer->writeEndDocument();
    delete writer;
    return true;
}
