#include "MainWindow.h"
#include "AppInfo.h"
#include "Log.h"
#include "VirtualReality.h"
#include "ui_MainWindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <boost/version.hpp>

MainWindow::MainWindow(VirtualReality &vr, QWidget *parent)
   : QMainWindow(parent)
   , vr(vr)
   , ui(new Ui::MainWindow)
   , VRviewer(new QVrViewer(vr, this))
   , VehicleViewer(new QVehicleViewer(vr, VRviewer))
{
   SET_FNAME("MainWindow::MainWindow()");
   ui->setupUi(this);
   startStopButton = new QPushButton("Start/Stop");
   startStopButton->setFixedSize(120, 40);
   startStopButton->setEnabled(true);
   connect(startStopButton, SIGNAL(clicked()), this, SLOT(startStopVR()));
   topViewButton = new QPushButton("Top view");
   topViewButton->setFixedSize(120, 40);
   topViewButton->setEnabled(true);
   connect(topViewButton, SIGNAL(clicked()), this, SLOT(setTopView()));
   bottomViewButton = new QPushButton("Bottom view");
   bottomViewButton->setFixedSize(120, 40);
   bottomViewButton->setEnabled(true);
   connect(bottomViewButton, SIGNAL(clicked()), this,
           SLOT(setBottomView()));
   perpendicularMoveAlongViewButton = new QPushButton("Perpendicular");
   perpendicularMoveAlongViewButton->setFixedSize(120, 40);
   perpendicularMoveAlongViewButton->setEnabled(true);
   connect(perpendicularMoveAlongViewButton, SIGNAL(clicked()), this,
           SLOT(perpendicularMoveAlongView()));
   quitButton = new QPushButton("Quit");
   quitButton->setFixedSize(120, 40);
   connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
   restartButton = new QPushButton("Restart");
   restartButton->setFixedSize(120, 40);
   connect(restartButton, SIGNAL(clicked()), this, SLOT(restart()));

   xSlider =
      createSlider(SIGNAL(xRotationChanged(int)), SLOT(setXRotation(int)));
   ySlider =
      createSlider(SIGNAL(yRotationChanged(int)), SLOT(setYRotation(int)));
   zSlider =
      createSlider(SIGNAL(zRotationChanged(int)), SLOT(setZRotation(int)));

   progressBar = new QProgressBar(this);
   progressBar->setValue(vr.getDirtLevel());

   // connect(VRviewer, SIGNAL(xRotationChanged(int)), xSlider,
   // SLOT(setValue(int)));
   // VehicleViewer->setFixedSize(150, 150);

   rightVerticalGroupBox = new QGroupBox;
   rightVerticalGroupBox->setMaximumWidth(250);
   auto *rvgbLayout = new QVBoxLayout;

   rvgbLayout->addWidget(startStopButton);
   rvgbLayout->addWidget(topViewButton);
   rvgbLayout->addWidget(bottomViewButton);
   rvgbLayout->addWidget(perpendicularMoveAlongViewButton);
   rvgbLayout->addWidget(restartButton);
   rvgbLayout->addWidget(quitButton);
   rvgbLayout->addWidget(new QLabel("Rx"));
   rvgbLayout->addWidget(xSlider);
   rvgbLayout->addWidget(new QLabel("Ry"));
   rvgbLayout->addWidget(ySlider);
   rvgbLayout->addWidget(new QLabel("Rz"));
   rvgbLayout->addWidget(zSlider);
   rvgbLayout->addWidget(new QLabel("Vehicle view"));
   rvgbLayout->addWidget(VehicleViewer);
   rvgbLayout->addWidget(new QLabel("Dirt level %"));
   rvgbLayout->addWidget(progressBar);
   rightVerticalGroupBox->setLayout(rvgbLayout);

   mainHorizontalGroupBox = new QGroupBox(this);
   QHBoxLayout *mhgbLayout = new QHBoxLayout;
   mhgbLayout->addWidget(VRviewer);
   mhgbLayout->addWidget(rightVerticalGroupBox);
   mainHorizontalGroupBox->setLayout(mhgbLayout);

   setCentralWidget(mainHorizontalGroupBox);

   xSlider->setValue(0);
   ySlider->setValue(0);
   zSlider->setValue(0);
   setWindowTitle(QString(APPNAME) + QString(" ") + QString(VERSION));
   createActions();
   createMenus();
   createStatusBar();

   setDirtLevel = new QTimer(this);
   setDirtLevel->setInterval(1000);
   connect(setDirtLevel, SIGNAL(timeout()), this, SLOT(showDirtLevel()));
   setDirtLevel->start(1000);

   LOGD("");
}

MainWindow::~MainWindow()
{
   SET_FNAME("MainWindow::~MainWindow()");
   vr.stopPhysics();
   delete VehicleViewer;
   delete VRviewer;
   delete ui;
   LOGD("");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
   event->accept();
}

QSlider *MainWindow::createSlider(const char *changedSignal,
                                  const char *setterSlot)
{
   auto slider = new QSlider(Qt::Horizontal);
   slider->setRange(0, 360);
   slider->setSingleStep(1);
   slider->setPageStep(15 * 16);
   slider->setTickInterval(15 * 16);
   slider->setTickPosition(QSlider::TicksRight);
   connect(slider, SIGNAL(valueChanged(int)), VRviewer, setterSlot);
   connect(VRviewer, changedSignal, slider, SLOT(setValue(int)));
   return slider;
}

void MainWindow::createActions()
{
   exitAction = new QAction(tr("&Quit"), this);
   // exitAction->setIcon(QIcon(":/images/exit.png"));
   exitAction->setShortcut(tr("Ctrl+Q"));
   exitAction->setStatusTip(tr("Exit the application"));
   connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

   aboutAction = new QAction(tr("A&bout"), this);
   aboutAction->setShortcut(tr("Ctrl+A"));
   aboutAction->setStatusTip(tr("Show the About box"));
   connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

   infoAction = new QAction(tr("I&nfo"), this);
   infoAction->setShortcut(tr("Ctrl+I"));
   infoAction->setStatusTip(tr("Show the Information box"));
   connect(infoAction, SIGNAL(triggered()), this, SLOT(info()));
}

void MainWindow::createMenus()
{
   helpMenu = menuBar()->addMenu(tr("&Help"));
   helpMenu->addAction(aboutAction);
   helpMenu->addAction(infoAction);
   menuBar()->addSeparator();
}

void MainWindow::createStatusBar() {}

void MainWindow::setTopView()
{
   VRviewer->setTopView();
}

void MainWindow::setBottomView()
{
   VRviewer->setBottomView();
}

void MainWindow::perpendicularMoveAlongView()
{
   VRviewer->togglePerpendicularMoveAlongView();
}

void MainWindow::restart()
{
   vr.init();
   progressBar->setValue(vr.getDirtLevel());
}

void MainWindow::about()
{
   static const QString bv(QString(BOOST_LIB_VERSION).replace("_", "."));
   QMessageBox::about(
      this, tr("About " APPNAME),
      tr("<h2>" APPNAME_VERSION "</h2>"
         "<p>Yet Another Autonomous Vehicle simulator.</p>"
         "<p>YAAV simulates the behavior of an autonomous vehicle in a 3D "
         "world."
         "</p>"
         "<p>Main goal: training autonomous vehicle programming.</p>"
         "<p>Developed by Jos Onokiewicz.</p>"
         "<p>This apllication uses:</p>"
         "<p>- Qt version ")
         .append(QT_VERSION_STR)
         .append("</p>"
                 "<p>- Boost C++ libraries version ")
         .append(bv)
         .append("\n</p>"));
}

void MainWindow::info()
{
   QMessageBox::about(this, tr("Info " APPNAME),
                      "<h2>" APPNAME_VERSION
                      "</h2>"
                      "<p>The 3D world contains a room, an autonomous "
                      "vacuum cleaner, objects and some dirt.</p>");
}
