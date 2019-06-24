#ifndef ADMINUI_H
#define ADMINUI_H
#include <QMainWindow>
#include <booksmodelviewtable.h>
#include <borrowmodelview.h>
#include <QAbstractProxyModel>
#include <QSortFilterProxyModel>
#include <QCloseEvent>
#include <QFile>
#include <QRegExp>
#include <QPixmap>
#include <formaddbook.h>
#include "user.h"
#include "usersmodelview.h"
#include "formuserinfo.h"

namespace Ui
{
class adminUI;
}

class adminUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminUI(QWidget *parent = 0, user *u = 0, usersmodelview *t = 0);
    ~adminUI();

private slots:
    void on_searchLine_textChanged(const QString &arg1);
    void on_autoreLine_textChanged(const QString &arg1);
    void on_genereLine_textChanged(const QString &arg1);
    void on_tableView_activated(const QModelIndex &index);
    void on_tableviewuser_activated(const QModelIndex &index);
    void closeEvent(QCloseEvent *);
    void on_addnewB_clicked();
    void on_pushButton_clicked();
    void on_deleteButton_clicked();
    void on_getBookButton_clicked();
    void on_returnButton_clicked();
    void on_removeUser_clicked();
    void on_tableUsersView_activated(const QModelIndex &index);
    void on_addUser_clicked();
    void on_actionExit_triggered();
    void on_actionAccount_informations_triggered();

    void on_sLineID_textChanged(const QString &arg1);

    void on_sLineName_textChanged(const QString &arg1);

    void on_sLineSname_textChanged(const QString &arg1);

private:
    //PROXY SHORT MODELS
    QSortFilterProxyModel booksPM;  //proxy sort model per il modello Gmodel
    QSortFilterProxyModel borrowPM; //proxy sort model per il modello userModel
    QSortFilterProxyModel usersPM;  //ps per gli utenti

    //UTENTE CHE HA FATTO LOGIN
    user *loginuser;

    //MODELS
    booksModelViewTable Gmodel; //modello generico per tutti i libri da visualizzare
    borrowModelView userModel;  //modello per i prestiti del utente
    usersmodelview *usersM;     //puntatore per il modello che ricevo da login contenente tutti gli utenti.
    Ui::adminUI *ui;
};

#endif // ADMINUI_H
