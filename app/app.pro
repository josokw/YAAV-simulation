# -------------------------------------------------
# Project created by QtCreator 2009-10-18T18:02:00
# -------------------------------------------------

QT += core gui opengl

TARGET = YAAVsimulator
TEMPLATE = app
CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -Wall -Wextra

SOURCES += main.cpp \
    MainWindow.cpp \
    Vehicle.cpp \
    VirtualReality.cpp \
    Room.cpp \
    QVrViewer.cpp \
    CylObject.cpp \
    Block.cpp \
    OrientationCone.cpp \
    Ball.cpp \
    DoPhysics.cpp \
    Dirt.cpp \
    EventQueue.cpp \
    Log.cpp \
    Ini.cpp \
    hardware/Sensor.cpp \
    hardware/Actuator.cpp \
    hardware/Timer.cpp \
    hardware/Memory.cpp \
    hardware/Bumper.cpp \
    hardware/Motor.cpp \
    hardware/IOextern.cpp \
    hardware/IOintern.cpp \
    hardware/Battery.cpp \
    utils/INIreader.cpp \
    utils/Logger.cpp \
    utils/stringExt.cpp \
    math/CartVec.cpp \
    math/MathDef.cpp \
    math/XYZrZ.cpp \
    math/Polygon.cpp \
    DynamicDirt.cpp \
    physics/CollisionDetector.cpp \
    QVehicleViewer.cpp

HEADERS += MainWindow.h \
    Vehicle.h \
    IOdef.h \
    DoPhysics.h \
    PhysicsState.h \
    PhysicsDef.h \
    VirtualReality.h \
    Drawable.h \
    Room.h \
    QVrViewer.h \
    AppInfo.h \
    PeriodicTask.h \
    Block.h \
    CylObject.h \
    OrientationCone.h \
    Ball.h \
    HWdef.h \
    Dirt.h \
    EventQueue.h \
    ExceptDef.h \
    Log.h \
    Ini.h \
    hardware/Sensor.h \
    hardware/Actuator.h \
    hardware/Timer.h \
    hardware/Memory.h \
    hardware/Bumper.h \
    hardware/Motor.h \
    hardware/Battery.h \
    hardware/IOintern.h \
    hardware/IOextern.h \
    hardware/IObus.h \
    utils/INIreader.h \
    utils/Logger.h \
    utils/stringExt.h \
    math/CartVec.h \
    math/MathDef.h \
    math/XYZrZ.h \
    DynamicDirt.h \
    math/Random.h \
    math/Polygon.h \
    physics/CollisionDetector.h \
    QVehicleViewer.h

OTHER_FILES += \
    YAAV.ini

FORMS += mainwindow.ui

DESTDIR = $$PWD/../build

INCLUDEPATH += \
   $$PWD \
   hardware \
   math \
   physics \
   utils

unix {
    LIBS += -L/usr/lib -lboost_thread
    LIBS += -L/usr/lib -lboost_program_options
    LIBS += -L/usr/lib -lboost_system
    LIBS += -L/usr/lib -lglut -lGLU
}

win32 { 
    INCLUDEPATH += $(BOOST_ROOT)
    LIBS += -L$(BOOST_LIBGCC) \
        -lboost_thread-mgw44-mt-d-1_47
    LIBS += -L$(BOOST_LIBGCC) \
        -lboost_filesystem-mgw44-mt-d-1_47
    LIBS += -L$(BOOST_LIBGCC) \
        -lboost_program_options-mgw44-mt-d-1_47
}

