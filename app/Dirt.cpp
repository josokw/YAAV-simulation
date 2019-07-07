#include "Dirt.h"

Dirt::Dirt(double R, const XYZrZ &xyzRz)
   : Drawable()
   , _R(R)
   , _XYZrZ(xyzRz)
   , _pBody(gluNewQuadric())
{
   // Drawable part
   gluQuadricDrawStyle(_pBody, GLU_FILL);
   gluQuadricTexture(_pBody, GLU_TRUE);
   gluQuadricNormals(_pBody, GLU_SMOOTH);
}

Dirt::Dirt(const Dirt &dirt)
   : Drawable()
   , _R(dirt.getR())
   , _XYZrZ(dirt.getXYZrZ())
   , _pBody(gluNewQuadric())
{
   gluQuadricDrawStyle(_pBody, GLU_FILL);
   gluQuadricTexture(_pBody, GLU_TRUE);
   gluQuadricNormals(_pBody, GLU_SMOOTH);
}

Dirt &Dirt::operator=(const Dirt &dirt)
{
   if (this != &dirt) {
      _R = dirt._R;
      _XYZrZ = dirt._XYZrZ;
      _pBody = gluNewQuadric();
      gluQuadricDrawStyle(_pBody, GLU_FILL);
      gluQuadricTexture(_pBody, GLU_TRUE);
      gluQuadricNormals(_pBody, GLU_SMOOTH);
   }
   return *this;
}

Dirt::~Dirt()
{
   gluDeleteQuadric(_pBody);
}

void Dirt::draw() const
{
   glPushMatrix();
   glColor3f(0.7, 0.7, 0.7);
   _XYZrZ.draw();
   GLfloat color[] = {1, 1, 1};
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
   gluSphere(_pBody, _R, 3, 3);
   glPopMatrix();
}
