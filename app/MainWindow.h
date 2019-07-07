#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QGroupBox>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QSplitter>
#include <QTimer>

#include "QVehicleViewer.h"
#include "QVrViewer.h"

namespace Ui {
class MainWindow;
}
class VirtualReality;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(VirtualReality &vr, QWidget *parent = nullptr);
   ~MainWindow();

protected:
   void closeEvent(QCloseEvent *event);

private:
   VirtualReality &vr;
   Ui::MainWindow *ui;
   QVrViewer *VRviewer;
   QVehicleViewer *VehicleViewer;
   QPushButton *startStopButton;
   QPushButton *topViewButton;
   QPushButton *bottomViewButton;
   QPushButton *perpendicularMoveAlongViewButton;
   QPushButton *quitButton;
   QPushButton *restartButton;
   QSlider *xSlider;
   QSlider *ySlider;
   QSlider *zSlider;
   QProgressBar *progressBar;
   QGroupBox *rightVerticalGroupBox;
   QGroupBox *mainHorizontalGroupBox;
   QSlider *createSlider(const char *changedSignal,
                         const char *setterSlot);
   QAction *aboutAction;
   QAction *infoAction;
   QAction *exitAction;
   QMenu *helpMenu;
   QTimer *setDirtLevel;
   void createActions();
   void createMenus();
   void createStatusBar();

private slots:
   void about();
   void info();
   void startStopVR()
   {
      vr.startStopPhysics();
      showDirtLevel();
   }
   void setTopView();
   void setBottomView();
   void perpendicularMoveAlongView();
   void restart();
   void showDirtLevel() { progressBar->setValue(vr.getDirtLevel()); }
};

#endif // MAINWINDOW_H
