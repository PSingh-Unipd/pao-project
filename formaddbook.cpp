#include "formaddbook.h"
#include "ui_formaddbook.h"
#include <QPixmap>
#include <QFileDialog>
#include <programmigbook.h>
#include <QMessageBox>
#include <QRegExp>


formAddBook::formAddBook(QWidget *parent=0, booksModelViewTable * model=0) :
    QDialog(parent),
    ui(new Ui::formAddBook),mod(model)
{
    ui->setupUi(this);
}


formAddBook::~formAddBook()
{
    delete ui;
}

void formAddBook::on_loadFile_clicked()
{
    QString file= QFileDialog::getOpenFileName(this, "Choise a cover for your book!", ":/",("Images (*.png *.jpg)"));
    QPixmap img(file);
    ui->lineIMGpaht->setText(file);
    ui->coverLabel->setScaledContents( true );
    ui->coverLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->coverLabel->setPixmap(img);
}

void formAddBook::on_addNewButton_clicked()
{
    QRegExp re("^[0-9]+$");
    QRegExpValidator *v = new QRegExpValidator(re);
    ui->isbnLine->setValidator(v);
    if(!ui->isbnLine->hasAcceptableInput() || ui->nameEdit->text().isEmpty() || ui->authorLine->text().isEmpty() || ui->subLine->text().isEmpty()){
        QMessageBox e;
        e.warning(this, "Dati non validi", "ISBN deve essere un numero! Nome libro,autore e isbn sono obbligatori!");
        return;
    }
    else{
        QString cover, desc, sub;
        cover=ui->lineIMGpaht->text();
        desc=ui->descText->toPlainText();
        sub=ui->subLine->text();
        if(ui->lineIMGpaht->text().isEmpty()){
            cover="nessuna";
        }
        if(ui->descText->toPlainText().isEmpty()){
            desc="nessuna";
        }
        if(ui->subLine->text().isEmpty()){
            sub="nessuno";
        }
        if(mod->addBook(ui->comboType->currentText(),ui->isbnLine->text(),cover,ui->nameEdit->text(),ui->authorLine->text(),desc, sub,ui->dateEdit->date() )){
            QMessageBox i;
            i.information(this, "Inserimento", "Libro inserito corretamente!");
        }else{
            QMessageBox er;
            er.critical(this,"Inserimento", "Errore durante inserimento! Impossibile inserire il libro!");
        }
    }
    this->close();
}

void formAddBook::on_addCancelButton_clicked()
{
    this->close();
}
