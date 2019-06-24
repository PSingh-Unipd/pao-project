#------------------------------------------
#
# Project created by Singh Parwinder
#
#------------------------------------------

QT       += core gui
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = progetto_p2
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
    classes/login.cpp \
    classes/book.cpp \
    classes/mathbook.cpp \
    classes/programmigbook.cpp \
    classes/user.cpp \
    classes/adminuser.cpp \
    classes/normaluser.cpp \
    classes/bookscontainer.cpp \
    classes/adminui.cpp \
    classes/booksmodelviewtable.cpp \
    classes/borrow.cpp \
    classes/borrowmodelview.cpp \
    classes/formaddbook.cpp \
    classes/usersmodelview.cpp \
    classes/formadduser.cpp \
    classes/formuserinfo.cpp

HEADERS  += login.h \
    headers/book.h \
    headers/mathbook.h \
    headers/programmigbook.h \
    headers/user.h \
    headers/adminuser.h \
    headers/normaluser.h \
    headers/bookscontainer.h \
    headers/adminui.h \
    headers/booksmodelviewtable.h \
    headers/borrow.h \
    headers/borrowmodelview.h \
    headers/formaddbook.h \
    headers/usersmodelview.h \
    headers/formadduser.h \
    headers/formuserinfo.h

FORMS    += login.ui \
    ui/adminui.ui \
    ui/formaddbook.ui \
    ui/formadduser.ui \
    ui/formuserinfo.ui

RESOURCES += \
    xml.qrc

DISTFILES +=
