#include "QVrViewer.h"
#include "Log.h"
#include "VirtualReality.h"
#include <QMouseEvent>
#include <QTimer>
#include <QWheelEvent>

QVrViewer::QVrViewer(VirtualReality &vr, QWidget *parent)
   : QGLWidget(parent)
   , isPerpendicular(false)
   , timer(new QTimer(this))
   , vr(&vr)
{
   SET_FNAME("QVrViewer::QVrViewer()");
   setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
   setMinimumSize(700, 600);

   cameraAngle[0] = 0.0;
   cameraAngle[1] = 0.0;
   cameraAngle[2] = 0.0;
   cameraPosition[0] = 0.0;
   cameraPosition[1] = 0.0;
   cameraPosition[2] = 3.5;

   rotationX = 0.0;
   rotationY = 0.0;
   rotationZ = 0.0;

   connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
   timer->setInterval(40);
   timer->start();
   LOGI("");
}

QVrViewer::~QVrViewer()
{
   SET_FNAME("QVrViewer::~QVrViewer()");
   delete timer;
   LOGI("");
}

void QVrViewer::initializeGL()
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

void QVrViewer::setXRotation(int angle)
{
   normalizeAngle(&angle);
   if (angle != rotationX) {
      rotationX = angle;
      emit xRotationChanged(angle);
      updateGL();
   }
}

void QVrViewer::setYRotation(int angle)
{
   normalizeAngle(&angle);
   if (angle != rotationY) {
      rotationY = angle;
      emit yRotationChanged(angle);
      updateGL();
   }
}

void QVrViewer::setZRotation(int angle)
{
   normalizeAngle(&angle);
   if (angle != rotationZ) {
      rotationZ = angle;
      // tell everyone we have changed the angle
      emit zRotationChanged(angle);
      updateGL();
   }
}

void QVrViewer::updateXRotation()
{
   static int angle = 0;
   normalizeAngle(&angle);
   setXRotation(angle++);
   updateGL();
}

void QVrViewer::setTopView()
{
   rotationX = 0.0;
   rotationY = 0.0;
   rotationZ = 0.0;
   updateGL();
}

void QVrViewer::setBottomView()
{
   rotationX = 180.0;
   rotationY = 0.0;
   rotationZ = 180.0;
   updateGL();
}

void QVrViewer::togglePerpendicularMoveAlongView()
{
   isPerpendicular = !isPerpendicular;
   updateGL();
}

void QVrViewer::resizeGL(int width, int height)
{
   // Prevent a divide by 0
   if (height == 0) {
      height = 1;
   }
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   GLfloat x = GLfloat(width) / height;
   glFrustum(-x, +x, -1.0, +1.0, 1.0, 200.0);
   glMatrixMode(GL_MODELVIEW);
}

void QVrViewer::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   draw();
}

void QVrViewer::draw()
{
   glMatrixMode(GL_MODELVIEW);
   // Initialize ModelView matrix
   glLoadIdentity();
   glRotatef(-cameraAngle[0], 1.0, 0.0, 0.0); // pitch
   glRotatef(-cameraAngle[1], 0.0, 1.0, 0.0); // heading
   glRotatef(-cameraAngle[2], 0.0, 0.0, 1.0); // roll
   if (isPerpendicular) {
      glTranslatef(-vr->m_vehicle.getXYZrZ().position.get_x(),
                   -vr->m_vehicle.getXYZrZ().position.get_y(),
                   -cameraPosition[2]);
   } else {
      glTranslatef(-cameraPosition[0], -cameraPosition[1],
                   -cameraPosition[2]);
   }
   // Transform the object, will modify the modeling matrix
   // Convert object coordinates to world coordinates
   glPushMatrix();
   glTranslatef(0, 0, 0);
   glRotatef(rotationX, 1.0, 0.0, 0.0);
   glRotatef(rotationY, 0.0, 1.0, 0.0);
   glRotatef(rotationZ, 0.0, 0.0, 1.0);
   vr->draw();
   glPopMatrix();
}

void QVrViewer::mousePressEvent(QMouseEvent *event)
{
   lastPos = event->pos();
}

void QVrViewer::mouseMoveEvent(QMouseEvent *event)
{
   GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
   GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

   if (event->buttons() & Qt::LeftButton) {
      rotationX += 300 * dy;
      rotationY += 300 * dx;
      updateGL();
   } else if (event->buttons() & Qt::RightButton) {
      rotationX += 300 * dy;
      rotationZ += 300 * dx;
      updateGL();
   }
   lastPos = event->pos();
}

void QVrViewer::wheelEvent(QWheelEvent *event)
{
   double cp2 = cameraPosition[2];
   cp2 += 0.03 * (event->delta() / 10);
   if (cp2 < 1.0)
      cp2 = 1.0;
   if (cp2 > 6.0)
      cp2 = 5.0;
   cameraPosition[2] = cp2;
   updateGL();
   lastPos = event->pos();
}

void QVrViewer::normalizeAngle(int *angle)
{
   while (*angle < 0)
      *angle += 360 * 16;
   while (*angle > 360 * 16)
      *angle -= 360 * 16;
}
