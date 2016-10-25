#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T23:53:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SolarisClient
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp \
    setting.cpp

HEADERS  += client.h \
    setting.h \
    structur.h

FORMS    += client.ui \
    setting.ui

RESOURCES += \
    res.qrc
