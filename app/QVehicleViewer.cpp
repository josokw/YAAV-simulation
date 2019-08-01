#include "QVehicleViewer.h"
#include "Log.h"
#include "VirtualReality.h"
#include <QMouseEvent>
#include <QTimer>

QVehicleViewer::QVehicleViewer(VirtualReality &vr, QWidget *parent)
   : QGLWidget(parent)
   , vr(&vr)
{
   SET_FNAME("QVehicleViewer::QVehicleViewer()");
   setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
   setMinimumSize(200, 200);

   cameraAngle[0] = 0.0;
   cameraAngle[1] = 0.0;
   cameraAngle[2] = 0.0;
   cameraPosition[0] = 0.0;
   cameraPosition[1] = 0.0;
   cameraPosition[2] = 0.1;

   QTimer *timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
   timer->setInterval(20);
   timer->start();
   LOGI("");
}

QVehicleViewer::~QVehicleViewer()
{
   SET_FNAME("QVehicleViewer::~QVehicleViewer()");
   LOGI("");
}

void QVehicleViewer::initializeGL()
{
   GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
   GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
   GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};

   qglClearColor(Qt::black);
   glShadeModel(GL_SMOOTH);
   glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
   glClearDepth(1.0);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   // glEnable(GL_CULL_FACE);
   glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
   glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
   glEnable(GL_LIGHT1);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void QVehicleViewer::resizeGL(int width, int height)
{
   // Prevent a divide by 0
   if (height == 0) {
      height = 1;
   }
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   GLfloat x = GLfloat(width) / height;
   glFrustum(-0.5 * x, +0.5 * x, -0.25, +0.25, 0.25, 500.0);
   glMatrixMode(GL_MODELVIEW);
}

void QVehicleViewer::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   draw();
}

void QVehicleViewer::draw()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   const double lookDistance = 0.5;
   double lookAtX =
      vr->vehicle_.getXYZrZ().position.get_x() +
      cos(math::toRadians(vr->vehicle_.getXYZrZ().Rz)) * lookDistance;
   double lookAtY =
      vr->vehicle_.getXYZrZ().position.get_y() +
      sin(math::toRadians(vr->vehicle_.getXYZrZ().Rz)) * lookDistance;
   double lookAtZ = 0.0;

   gluLookAt(vr->vehicle_.getXYZrZ().position.get_x(),
             vr->vehicle_.getXYZrZ().position.get_y(),
             vr->vehicle_.getH() + 0.2, lookAtX, lookAtY, lookAtZ, 0, 0,
             1);

   glPushMatrix();
   vr->draw();
   glPopMatrix();
}
