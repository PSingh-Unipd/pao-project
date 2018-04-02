#include "adminui.h"
#include "ui_adminui.h"
#include "formadduser.h"
adminUI::adminUI(QWidget *parent, user* u, usersmodelview * t) :
    QMainWindow(parent),usersM(t), loginuser(u),
    ui(new Ui::adminUI)
{
   ui->setupUi(this);

   //CARICO I DATI NEI MODELLI
   QFile f("books.xml");//lettura statica dei file xml
   QFile f2("borrow.xml");
   Gmodel.setModelContainer(f);
   userModel.loadUserBorrow(f2);

   //IMPOSTO I MODELLI PER I PROXY MODEL
   booksPM.setSourceModel(&Gmodel);
   borrowPM.setSourceModel(&userModel);
   usersPM.setSourceModel(usersM);

   //ESPRESIONE REGOLARE PER VISUALIZZARE SOLO PRESTITI DEL UTENTE CHE HA FATTO LOGIN
   QRegExp reg(u->getUname(), Qt::CaseInsensitive, QRegExp::Wildcard);
   borrowPM.setFilterRegExp(reg);
   borrowPM.setFilterKeyColumn(4);

   //CARICO I MODELLI NEI VARI TABLEVIEW
   ui->tableView->setModel(&booksPM);
   ui->tableviewuser->setModel(&borrowPM);
   ui->tableviewuser->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

   //CONTROLLO CHE TIPO DI UTEMNTE è BASE A QUELLO GENERO L'INTERFACCIA
   if(u->getType()=="normal"){//utente normale allora nascondo alcuni tasti
       ui->addnewB->hide();//nascondo il tasto per aggiungerre nuovo libro
       ui->deleteButton->hide();//nascondo il tasto per eliminare un libro
       ui->maintab->removeTab(2);//elimino il tab per la gestione degli utente(inserimenti o cancellazione)
   }
   if(u->getType()=="admin"){
       ui->tableUsersView->setModel(&usersPM);
       ui->tableUsersView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   }

}

adminUI::~adminUI()
{
       delete ui;
}
void adminUI::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Avviso importante");
    msgBox.setText("Se non hai cliccato il pulsante 'AGGIORNA DATABASE' tutte le modifiche fatte andranno perse. Sei sicuro di voler uscire?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes, "Si");
    msgBox.setButtonText(QMessageBox::No, "No");
    if(msgBox.exec() == QMessageBox::Yes){
        event->accept();
    }else{
        event->ignore();
    }

}

void adminUI::on_searchLine_textChanged(const QString &arg1)
{
      QRegExp reg(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
      booksPM.setFilterRegExp(reg);
      booksPM.setFilterKeyColumn(1);
      ui->tableView->setModel(&booksPM);
}

void adminUI::on_autoreLine_textChanged(const QString &arg1)
{
    QRegExp reg(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    booksPM.setFilterRegExp(reg);
    booksPM.setFilterKeyColumn(2);
    ui->tableView->setModel(&booksPM);
}

void adminUI::on_genereLine_textChanged(const QString &arg1)
{
    QRegExp reg(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    booksPM.setFilterRegExp(reg);
    booksPM.setFilterKeyColumn(4);
    ui->tableView->setModel(&booksPM);
}

void adminUI::on_tableView_activated(const QModelIndex &index)
{
    QString val= ui->tableView->model()->data(index.child(index.row(),0)).toString();
    ui->lineIS->setText(Gmodel.data(Gmodel.index(index.row(), 0), Qt::DisplayRole).toString());
    ui->lineName->setText(Gmodel.data(Gmodel.index(index.row(), 1), Qt::DisplayRole).toString());
    ui->lineA->setText(Gmodel.data(Gmodel.index(index.row(), 2), Qt::DisplayRole).toString());
    ui->lineCP->setText(Gmodel.data(Gmodel.index(index.row(), 6), Qt::DisplayRole).toString());
    ui->lineDate->setText(Gmodel.data(Gmodel.index(index.row(), 3), Qt::DisplayRole).toString());
    ui->lineDesc->setText(Gmodel.data(Gmodel.index(index.row(), 5), Qt::DisplayRole).toString());
    QPixmap img,nocover(":/img/nocoverava.jpg");
    ui->coverLabel->setScaledContents( true );
    ui->coverLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    if(img.load(Gmodel.getCover(val))){
      ui->coverLabel->setPixmap(img);
    }else{
      ui->coverLabel->setPixmap(nocover);
    }
}

void adminUI::on_tableviewuser_activated(const QModelIndex &index)
{
    QString val= ui->tableviewuser->model()->data(index.child(index.row(),0)).toString();
    bool cond=false;
    int r= Gmodel.rowCount(index);
    for(int i=0; i<r && !cond; i++){
        QString temp=Gmodel.data(Gmodel.index(i, 0), Qt::DisplayRole).toString();
        if(temp==val){
            cond=true;
            ui->lineISU->setText(ui->tableviewuser->model()->data(index.child(index.row(),0)).toString());
            ui->lineNameU->setText(Gmodel.data(Gmodel.index(i, 1), Qt::DisplayRole).toString());
            ui->lineAU->setText(Gmodel.data(Gmodel.index(i, 2), Qt::DisplayRole).toString());
            ui->lineDateU->setText(Gmodel.data(Gmodel.index(i, 3), Qt::DisplayRole).toString());
            ui->lineDescU->setText(Gmodel.data(Gmodel.index(i, 5), Qt::DisplayRole).toString());
            QPixmap img,nocover(":/img/nocoverava.jpg");
            ui->coverLabelU->setScaledContents(true);
            ui->coverLabelU->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            if(img.load(Gmodel.getCover(temp))){
              ui->coverLabelU->setPixmap(img);
            }else{
              ui->coverLabelU->setPixmap(nocover);
            }
        }
    }
}

void adminUI::on_addnewB_clicked(){
    formAddBook b(this, &Gmodel);//passo il modello al form per aggiunger un nuovo libro, cosi il libro vieni aggiunto direttamente al form nella implementazione d
    b.exec();
}

void adminUI::on_pushButton_clicked()
{
    QFile f("books.xml");
    QFile f2("borrow.xml");
    QFile f3("users.xml");
    if(Gmodel.saveData(f) && userModel.saveData(f2) && usersM->saveData(f3)){
        QMessageBox con;
        con.information(this,"Aggiornamento", "Databse aggiornato correttamente!" );
    }
}

void adminUI::on_deleteButton_clicked()
{
    QString is=ui->lineIS->text();
    if(is.isEmpty()){
        QMessageBox war;
        war.critical(this, "Errore", "Selezionare un libro dalla tabella per eliminare un libro!");
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Richiesta");
        msgBox.setText("Vuoi rimuovere solo una copia oppure tutte le copie? Attenzione: puoi rimuovere tutte le copie contemporaneamente solo se nessuna di essa e' in prestito!");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, "Una sola copia");
        msgBox.setButtonText(QMessageBox::No, "Tutte le copie");
        if(msgBox.exec() == QMessageBox::Yes){
            Gmodel.removeCopy(ui->lineIS->text());
            QMessageBox infoc;
            infoc.information(this, "Eliminazione", "Copia eliminata con successo!");
        }
        else{
            bool cond=false;
            int r= userModel.rowCount(QModelIndex());
            for(int i=0; i<r && !cond; i++){
                QString temp=userModel.data(userModel.index(i, 0), Qt::DisplayRole).toString();
                if(temp==ui->lineIS->text())
                    cond=true;
            }
                if(!cond){
                        if(Gmodel.removeBook(is)){
                            ui->lineIS->clear();
                            ui->lineA->clear();
                            ui->lineDate->clear();
                            ui->lineName->clear();
                            ui->lineDesc->clear();
                            ui->lineCP->clear();
                            QMessageBox info;
                            info.information(this, "Eliminazione", "Libro eliminato con successo!");
                        }else{
                            QMessageBox err;
                            err.critical(this, "Eliminazione", "Errore durante eliminazione del libro!");
                        }
               }else{
                    QMessageBox war2;
                    war2.warning(this, "Fallimento", "Impossibile eliminare tutte le copie, poiche una o piu copie sono in prestito.");

                }
        }


}
}
void adminUI::on_getBookButton_clicked()
{
    QString is=ui->lineIS->text();
    if(is.isEmpty()){
        QMessageBox war;
        war.critical(this, "Errore", "Selezionare un libro dalla tabella prima di chiedere il prestito!");
    }
    else{
        if(ui->lineCP->text()=="0"){
            QMessageBox err1;
            err1.critical(this, "Errore", "Impossibile effetuare il prestito. Poiche ci sono 0 copie disponibili per questo libro!");

        }
        else{
            QDate sd, ed;
            sd=QDate::currentDate();
            ed.setDate(sd.year(), sd.month()+1, sd.day());
            userModel.addBorrow(loginuser->getUname(),ui->lineIS->text(),ui->lineName->text(),sd, ed );
            Gmodel.removeCopy(ui->lineIS->text());
            QMessageBox ok;
            ok.information(this, "Prestito", "Prestito fatto correttamente!");
        }
    }
}



void adminUI::on_returnButton_clicked()
{
    QString is=ui->lineISU->text();
    if(is.isEmpty()){
        QMessageBox war;
        war.critical(this, "Errore", "Selezionare un prestito dalla tabella prima!");
    }
    else{
        if(userModel.removeBorrow(loginuser->getUname(), is)){
            Gmodel.addCopy(ui->lineISU->text());
            ui->lineISU->clear();
            ui->lineAU->clear();
            ui->lineDateU->clear();
            ui->lineNameU->clear();
            ui->lineDescU->clear();
            QMessageBox info;
            info.information(this, "Operazione eseguita", "Libro restituito!");
        }else{
            QMessageBox err;
            err.critical(this, "Errore", "Errore durante la restituzione del libro!");
        }
    }
}

void adminUI::on_removeUser_clicked()
{
    QString is=ui->lineIDU->text();
    if(is.isEmpty()){
        QMessageBox war;
        war.critical(this, "Errore", "Selezionare un utente prima di eliminarlo!");
    }
    else{
        if(usersM->removeUser(is)){
            ui->lineIDU->clear();
            QMessageBox info;
            info.information(this, "Eliminazione", "Utente eliminato con successo!");
        }else{
            QMessageBox err;
            err.critical(this, "Eliminazione", "Errore durante eliminazione dell'utente!");
        }
    }
}

void adminUI::on_tableUsersView_activated(const QModelIndex &index)
{
    QString val= ui->tableUsersView->model()->data(index.child(index.row(),0)).toString();
    ui->lineIDU->setText(val);
}

void adminUI::on_addUser_clicked()
{
    formAddUser b(this, usersM);//passo il modello al form per aggiunger un nuovo libro, cosi il libro vieni aggiunto direttamente al form nella implementazione d
    b.exec();
}

void adminUI::on_actionExit_triggered()
{
    this->close();
}

void adminUI::on_actionAccount_informations_triggered()
{
    FormUserInfo b(this,loginuser);
    b.exec();
}

void adminUI::on_sLineID_textChanged(const QString &arg1)
{
    QRegExp reg(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    usersPM.setFilterRegExp(reg);
    usersPM.setFilterKeyColumn(0);
    ui->tableUsersView->setModel(&usersPM);
}

void adminUI::on_sLineName_textChanged(const QString &arg1)
{
    QRegExp reg(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    usersPM.setFilterRegExp(reg);
    usersPM.setFilterKeyColumn(1);
    ui->tableUsersView->setModel(&usersPM);
}

void adminUI::on_sLineSname_textChanged(const QString &arg1)
{
    QRegExp reg(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    usersPM.setFilterRegExp(reg);
    usersPM.setFilterKeyColumn(2);
    ui->tableUsersView->setModel(&usersPM);
}
