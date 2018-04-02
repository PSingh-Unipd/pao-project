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
        login.cpp \
    book.cpp \
    mathbook.cpp \
    programmigbook.cpp \
    user.cpp \
    adminuser.cpp \
    normaluser.cpp \
    bookscontainer.cpp \
    adminui.cpp \
    booksmodelviewtable.cpp \
    borrow.cpp \
    borrowmodelview.cpp \
    formaddbook.cpp \
    usersmodelview.cpp \
    formadduser.cpp \
    formuserinfo.cpp

HEADERS  += login.h \
    book.h \
    mathbook.h \
    programmigbook.h \
    user.h \
    adminuser.h \
    normaluser.h \
    bookscontainer.h \
    adminui.h \
    booksmodelviewtable.h \
    borrow.h \
    borrowmodelview.h \
    formaddbook.h \
    usersmodelview.h \
    formadduser.h \
    formuserinfo.h

FORMS    += login.ui \
    adminui.ui \
    formaddbook.ui \
    formadduser.ui \
    formuserinfo.ui

RESOURCES += \
    xml.qrc

DISTFILES +=
