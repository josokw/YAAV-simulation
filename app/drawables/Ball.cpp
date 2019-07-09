#include "Ball.h"

Ball::Ball(double R, const XYZrZ &xyzRz)
   : Drawable()
   , R_(R)
   , XYZrZ_(xyzRz)
   , pBody_(gluNewQuadric())
{
   // Drawable part
   gluQuadricDrawStyle(pBody_, GLU_FILL);
   gluQuadricTexture(pBody_, GLU_TRUE);
   gluQuadricNormals(pBody_, GLU_SMOOTH);
}

void Ball::draw() const
{
   glPushMatrix();
   glColor3f(0.3f, 0.7f, 0.2f);
   XYZrZ_.draw();
   GLfloat color[] = {1, 1, 1};
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
   gluSphere(pBody_, R_, 30, 30);
   glPopMatrix();
}
