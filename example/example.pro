#-------------------------------------------------------------------------
# A simple example that uses TLDExtractor
#
# TLDExtractor, a simple Qt interface to extract TLD part of a host
# Copyright (C) 2014  Razi Alavizadeh <s.r.alavizadeh@gmail.com>
#
# Project created by QtCreator 2014-12-04T15:32:18
#
#-------------------------------------------------------------------------

TARGET = TLDExtractor

TEMPLATE = app

QT += core gui

include(../tldextractor.pri)

SOURCES += main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h
