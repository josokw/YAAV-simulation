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
   PolygonTests.cpp \
   XYZrZtests.cpp \
   ../app/math/CartVec.cpp \
   ../app/math/Circle.cpp \
   ../app/math/Point.cpp \
   ../app/math/Polygon.cpp \
   ../app/math/XYZrZ.cpp \
   ../app/math/MathDef.cpp

INCLUDEPATH += \
   ../app \
   ../lib \
   ../app/math \
   ../app/drawables

DESTDIR = $$PWD/../build
