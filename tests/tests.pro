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
   CollisionDetectorTests.cpp \
   ../app/math/CartVec.cpp \
   ../app/math/Circle.cpp \
   ../app/math/Point.cpp \
   ../app/math/Polygon.cpp \
   ../app/math/XYZrZ.cpp \
   ../app/math/MathDef.cpp \
   ../app/physics/CollisionDetector.cpp \
   ../app/utils/Logger.cpp \
   ../app/Log.cpp 

INCLUDEPATH += \
   ../app \
   ../lib \
   ../app/math \
   ../app/drawables \
   ../app/physics \
   ../app/utils 

DESTDIR = $$PWD/../build

unix {
    LIBS += -L/usr/lib -lboost_thread
    LIBS += -L/usr/lib -lboost_program_options
    LIBS += -L/usr/lib -lboost_system
    LIBS += -L/usr/lib -lglut -lGLU
}
