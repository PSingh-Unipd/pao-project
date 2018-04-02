#ifndef BOOKSCONTAINER_H
#define BOOKSCONTAINER_H
#include<vector>
#include "book.h"
#include <QFile>
#include <QXmlStreamReader>
using std::vector;

//Contenitore che contiene i puntatori ai book e un intero che serve per specificare il numero di copie di quel oggetto.
//Quindi invece di dupplicare un oggetto se è gia presente nel contenitore incremento l'intero.
class bookscontainer
{   friend class iterator;
private:
    class node {//solita classe nodo
    public:
        book* info;
        node* prev;
        node* next;
        int nc; //numero di copie per ogni libro, motivo per il quale ho creata questo contenitore.
        node(book*, node*, node*, int);
    };
    node* first;//puntatore al primo elemento
    node* last;//puntatore al ultimo elemento

    //COPIA PROFONDA
    static node* DeepCopy(node*);
    static node* GetLast(node*);
    static void DeepDelete(node*);
public:


    class iterator {
    friend class bookscontainer;
    private:
        bookscontainer::node* punt;
    public:
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
    };



    bookscontainer();

    //COPIA PROFONDA
    bookscontainer(const bookscontainer&);//COSTRUTORE DI COPIA PROFONDO
    ~bookscontainer();//DISTRUTTORE PROFONDO
    bookscontainer& operator=(const bookscontainer&);//ASSEGNAZIONE PROFONDO


   //ALTRI METODI CLASSICI
    bookscontainer::iterator begin() const;
    bookscontainer::iterator end() const;
    void addBook(book*, unsigned int);
    bool removeAllCopies(QString&);//riceve un isbn e rimuove tutte le copie del libro con quel isbn (forse era meglio un libro invece di un isbn?)
    unsigned int size() const;//restituisce la dimensione del contenitore
    book* operator[](const iterator& )const;
    book* operator[](unsigned int) const;

    //METODI PER MODIFICARE O LEGGERE L INTERO CHE CONTIENE IL NUMERO DI COPIE - motivo per il quale e' stato implementato questo contenitore
    int getCN(const book*)const;//restitusce il numero di copie per un dato libro
    void incCN(const book*);//metodo per incrementare
    void decCN(const book*);//metodo per deincrementare
    };

#endif // BOOKSCONTAINER_H
