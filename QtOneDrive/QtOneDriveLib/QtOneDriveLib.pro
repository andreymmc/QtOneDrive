#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T13:04:10
#
#-------------------------------------------------

QT       += widgets network webkitwidgets

QT       -= gui

TARGET = QtOneDriveLib
TEMPLATE = lib


CONFIG += c++11

DEFINES += QTONEDRIVELIB_LIBRARY

SOURCES += qtonedrive.cpp \
    qtonedriverequest.cpp \
    authorizationform.cpp

HEADERS += qtonedrive.h\
        qtonedrivelib_global.h \
    qtonedriverequest.h \
    authorizationform.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    authorizationform.ui

OTHER_FILES += \
    ../one-drive.php \
    OneDrive.png
