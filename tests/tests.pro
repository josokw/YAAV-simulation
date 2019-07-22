QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YAAVsimulatorUnitTests
TEMPLATE = app

CONFIG += console
CONFIG += c++17

SOURCES += \
   testMain.cpp \
   CircleTests.cpp \
   CartVecTests.cpp \
   PointTests.cpp \
   ../app/math/CartVec.cpp \
   ../app/math/Circle.cpp \
   ../app/math/Point.cpp

HEADERS +=

INCLUDEPATH += \
   ../app \
   ../lib \
   ../app/math

DESTDIR = $$PWD/../build
