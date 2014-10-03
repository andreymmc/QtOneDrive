#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T13:05:51
#
#-------------------------------------------------

QT       += core network gui webkitwidgets

TARGET = QtOneDriveApp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += TEST_QTONEDRIVE

CONFIG += c++11

SOURCES += main.cpp \
   ../QtOneDriveLib/qtonedrive.cpp \
    ../QtOneDriveLib/qtonedriveauthorizationdialog.cpp \
    ../QtOneDriveLib/qtonedrivewebview.cpp \
    testdialog.cpp

HEADERS += \
    ../QtOneDriveLib/qtonedrive.h \
    ../QtOneDriveLib/qtonedriveauthorizationdialog.h \
    ../QtOneDriveLib/qtonedrivewebview.h \
    testdialog.h

FORMS += \
    testdialog.ui

OTHER_FILES +=
