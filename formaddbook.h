#ifndef FORMADDBOOK_H
#define FORMADDBOOK_H

#include <QDialog>
#include "booksmodelviewtable.h"
namespace Ui {
class formAddBook;
}

class formAddBook : public QDialog
{
    Q_OBJECT

public:
    formAddBook(QWidget *parent, booksModelViewTable *);
    ~formAddBook();

private slots:
    void on_loadFile_clicked();

    void on_addNewButton_clicked();

    void on_addCancelButton_clicked();

private:
    Ui::formAddBook *ui;
    booksModelViewTable *mod;
};

#endif // FORMADDBOOK_H
