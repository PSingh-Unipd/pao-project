#include "bookscontainer.h"
#include <QMessageBox>
#include <programmigbook.h>
#include <mathbook.h>
#include <QDebug>

bookscontainer::bookscontainer()
    : first(0), last(0) {}

bookscontainer::node::node(book *i, node *p, node *n, int x) //costruttore del nodo
    : info(i), prev(p), next(n), nc(x)
{
}

void bookscontainer::DeepDelete(node *p)
{
    if (p)
    {
        DeepDelete(p->next);
        delete p;
    }
}

bookscontainer::node *bookscontainer::DeepCopy(node *n)
{
    if (!n)
        return 0;
    node *t = new node(n->info, 0, 0, n->nc);
    node *p = t;
    while (n->next)
    {
        p->next = new node(n->next->info, p, 0, n->next->nc);
        p = p->next;
        n = n->next;
    }
    return t;
}

bookscontainer::node *bookscontainer::GetLast(node *n)
{
    if (!n)
        return 0;
    while (n->next)
        n = n->next;
    return n;
}

bookscontainer::bookscontainer(const bookscontainer &l) : first(DeepCopy(l.first)), last(GetLast(first)) {}

bookscontainer::~bookscontainer() { DeepDelete(first); }

bookscontainer &bookscontainer::operator=(const bookscontainer &l)
{
    if (this != &l)
    {
        node *temp = first;
        first = DeepCopy(l.first);
        last = GetLast(first);
        DeepDelete(temp);
    }
    return *this;
}

bool bookscontainer::iterator::operator==(const iterator &it) const
{
    return punt == it.punt;
}

bool bookscontainer::iterator::operator!=(const iterator &it) const
{
    return punt != it.punt;
}

bookscontainer::iterator &bookscontainer::iterator::operator++()
{
    if (punt)
        punt = punt->next;
    return *this;
}

bookscontainer::iterator bookscontainer::iterator::operator++(int)
{
    iterator aux = *this;
    if (punt)
        punt = punt->next;
    return aux;
}

bookscontainer::iterator &bookscontainer::iterator::operator--()
{
    if (punt)
        punt = punt->prev;
    return *this;
}

bookscontainer::iterator bookscontainer::iterator::operator--(int)
{
    iterator aux = *this;
    if (punt)
        punt = punt->prev;
    return aux;
}

bookscontainer::iterator bookscontainer::begin() const
{
    iterator aux;
    aux.punt = first;
    return aux;
}

bookscontainer::iterator bookscontainer::end() const
{
    iterator aux;
    aux.punt = 0;
    return aux;
}

book *bookscontainer::operator[](const iterator &it) const
{
    return (it.punt)->info;
}

void bookscontainer::addBook(book *b, unsigned int x = 1)
{
    bool found = false;
    for (bookscontainer::iterator it = this->begin(); it != this->end(); it++)
    {
        if (it.punt->info->getISBN() == b->getISBN() && !found)
        {
            found = true;
            it.punt->nc++;
        }
    }
    if (!found)
    {
        if (last)
        {
            last = new node(b, last, 0, x);
            (last->prev)->next = last;
        }
        else
            first = last = new node(b, 0, 0, x);
    }
}

book *bookscontainer::operator[](unsigned int a) const
{
    book *copy;
    unsigned int x = 0;
    bool found = false;
    for (bookscontainer::iterator it = this->begin(); it != this->end(); it++)
    {
        if (x == a && !found)
        {
            copy = (*this)[it];
            found = true;
        }
        x++;
    }
    if (found)
        return copy;
    else
        return 0;
}
bool bookscontainer::removeAllCopies(QString &is)
{
    node *n = first;
    node *p = 0;
    while (n && n->info->getISBN() != is)
    {
        p = n;
        n = n->next;
    }
    if (n)
    {
        if (!p)
        {
            first = n->next;
            if (n->next)
                n->next->prev = 0;
        }
        else if (n->next)
        {
            p->next = n->next;
            n->next->prev = p;
        }
        else
        {
            p->next = 0;
            last = p;
        }
        delete n;
    }
    else
        return false;
    return true;
}

unsigned int bookscontainer::size() const
{
    if (!first)
        return 0;
    unsigned int size = 1;
    node *n = first;
    while (n->next)
    {
        size++;
        n = n->next;
    }
    return size;
}

int bookscontainer::getCN(const book *p) const
{
    for (bookscontainer::iterator it = this->begin(); it != this->end(); it++)
    {
        if (p->getISBN() == it.punt->info->getISBN())
        {
            return it.punt->nc;
        }
    }
    return 0;
}

void bookscontainer::incCN(const book *b)
{
    for (bookscontainer::iterator it = this->begin(); it != this->end(); it++)
    {
        if (b->getISBN() == (*this)[it]->getISBN())
        {
            it.punt->nc++;
            return;
        }
    }
}
void bookscontainer::decCN(const book *b)
{
    for (bookscontainer::iterator it = this->begin(); it != this->end(); it++)
    {
        if (b->getISBN() == (*this)[it]->getISBN())
        {
            if (it.punt->nc > 0)
                it.punt->nc--;
            return;
        }
    }
}
