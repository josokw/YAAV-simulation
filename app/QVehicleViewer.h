#ifndef QVEHICLEVIEWER_H
#define QVEHICLEVIEWER_H

#include "VirtualReality.h"

class QVehicleViewer : public QGLWidget
{
   Q_OBJECT

public:
   /// @todo vr is shared, needs mutex protection
   QVehicleViewer(VirtualReality &vr, QWidget *parent = nullptr);
   virtual ~QVehicleViewer();
   QVehicleViewer(const QVehicleViewer &) = delete;
   QVehicleViewer &operator=(const QVehicleViewer &) = delete;

protected:
   void initializeGL();
   void resizeGL(int width, int height);
   void paintGL();

private:
   void draw();

   GLfloat cameraAngle[3];
   GLfloat cameraPosition[3];

public:
   VirtualReality *vr;
};

#endif // QVEHICLEVIEWER_H
