#-------------------------------------------------
#
# Project created by QtCreator 2011-01-12T20:29:57
#
#-------------------------------------------------

QT       += core network
QT       += testlib
QT       -= gui

TARGET = QtHessian
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    hexception.cpp \
    hcore/hnetworkmanager.cpp \
    hcore/houtputstream.cpp \
    hcore/hinputstream.cpp \
    test/hnetworktest.cpp \
    hcore/hcall.cpp \
    test/hnetworkatest.cpp \
    test/performancetest.cpp \
    hunittest.cpp

HEADERS += \
    hcore/hobject.h \
    hexception.h \
    hcore/hnetworkmanager.h \
    hcore/houtputstream.h \
    hcore/hinputstream.h \
    test/hnetworktest.h \
    hcore/hcall.h \
    test/hnetworkatest.h \
    hcore/hconstants.h \
    test/performancetest.h \
    QtHessian.h \
    hunittest.h
