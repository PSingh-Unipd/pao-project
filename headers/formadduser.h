#ifndef FORMADDUSER_H
#define FORMADDUSER_H

#include "usersmodelview.h"
#include <QDialog>

namespace Ui {
class formAddUser;
}

class formAddUser : public QDialog
{
    Q_OBJECT

public:
    explicit formAddUser(QWidget *parent, usersmodelview *);
    ~formAddUser();

private slots:
    void on_addUserCancel_clicked();

    void on_addUser_clicked();

private:
    Ui::formAddUser *ui;
    usersmodelview* mod;
};

#endif // FORMADDUSER_H
