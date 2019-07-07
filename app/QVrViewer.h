#ifndef QVRVIEWER_H
#define QVRVIEWER_H

#include <QGLWidget>

#include "VirtualReality.h"

class QVrViewer : public QGLWidget
{
   Q_OBJECT

public:
   QVrViewer(VirtualReality &vr, QWidget *parent = nullptr);
   ~QVrViewer();

   // The holders for the values for the rotation
   int xRotation() const { return rotationX; }
   int yRotation() const { return rotationY; }
   int zRotation() const { return rotationZ; }

public slots:
   void setXRotation(int angle);
   void setYRotation(int angle);
   void setZRotation(int angle);
   void updateXRotation();
   void setTopView();
   void setBottomView();
   void togglePerpendicularMoveAlongView();

signals:
   void xRotationChanged(int angle);
   void yRotationChanged(int angle);
   void zRotationChanged(int angle);

protected:
   void initializeGL();
   void resizeGL(int width, int height);
   void paintGL();
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
   void wheelEvent(QWheelEvent *event);

private:
   void draw();
   void normalizeAngle(int *angle);

   GLfloat cameraAngle[3];
   GLfloat cameraPosition[3];

   GLfloat rotationX;
   GLfloat rotationY;
   GLfloat rotationZ;
   QPoint lastPos;
   bool isPerpendicular;
   QTimer *timer;

public:
   VirtualReality *vr;
};

#endif // QVRVIEWER_H
