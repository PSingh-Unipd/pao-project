#include "login.h"
#include "ui_login.h"
#include "adminui.h"
#include "usersmodelview.h"
#include <QFile>
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_loginB_clicked()
{
  if(!ui->userLine->text().isEmpty() && !ui->passLine->text().isEmpty()){
      QFile f("users.xml");
      usersmodelview *model= new usersmodelview();
      model->loadUsers(f);
      user* t= model->find(ui->userLine->text());
      if(t!=0){
          if(t->getUname()==ui->userLine->text()&& t->getPassword()==ui->passLine->text() ){
              adminUI* q= new adminUI(0,t, model);
              q->show();
              this->close();
          }else{
              QMessageBox err3;
              err3.critical(0, "Errore login","Password non corretta!" );
          }
      }else{
          QMessageBox err2;
          err2.critical(0, "Errore login", "Utente non trovato!");
      }
  }else{
      QMessageBox err;
      err.critical(0, "Errore login", "Nome utente e la password sono obbligatori!");
  }
}

void login::on_cancelB_clicked()
{
    this->close();
}
