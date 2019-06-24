#include "login.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include "bookscontainer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    w.show();

    return a.exec();
}
