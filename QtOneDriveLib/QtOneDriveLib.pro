#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T13:04:10
#
#-------------------------------------------------

QT       += widgets network webkitwidgets gui core

TARGET = QtOneDriveLib
TEMPLATE = lib

CONFIG += c++11

DEFINES += QTONEDRIVELIB_LIBRARY

SOURCES += qtonedrive.cpp \
    qtonedriveauthorizationdialog.cpp \
    qtonedrivewebview.cpp

HEADERS += qtonedrive.h\
        qtonedrivelib_global.h \
    qtonedriveauthorizationdialog.h \
    qtonedrivewebview.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS +=

OTHER_FILES += \
    ../one-drive.php \
    OneDrive.png

RESOURCES +=
