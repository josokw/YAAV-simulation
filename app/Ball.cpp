#include "Ball.h"

Ball::Ball(double R, const XYZrZ &xyzRz)
   : Drawable()
   , m_R(R)
   , m_XYZrZ(xyzRz)
   , m_pBody(gluNewQuadric())
{
   // Drawable part
   gluQuadricDrawStyle(m_pBody, GLU_FILL);
   gluQuadricTexture(m_pBody, GLU_TRUE);
   gluQuadricNormals(m_pBody, GLU_SMOOTH);
}

void Ball::draw() const
{
   glPushMatrix();
   glColor3f(0.3, 0.7, 0.2);
   m_XYZrZ.draw();
   GLfloat color[] = {1, 1, 1};
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
   gluSphere(m_pBody, m_R, 30, 30);
   glPopMatrix();
}
