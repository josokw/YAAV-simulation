#include "CylObject.h"
#include <ios>
#include <iostream>

std::istream &operator>>(std::istream &is, CylObject &rhs)
{
   double R = 0.0;
   double H = 0.0;
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;
   double Rz = 0.0;
   is >> R >> H >> x >> y >> z >> Rz;
   // only if everything is ok, output parameter v will be changed
   if (is) {
      rhs = CylObject(R, H, XYZrZ(x, y, z, Rz));
   }
   return is; // client code should check state of is
}

CylObject::CylObject(double R, double H, const XYZrZ &xyzRz)
   : _R(R)
   , _H(H)
   , _XYZrZ(xyzRz)
   , _pBody(gluNewQuadric())
{
   // Drawable part
   gluQuadricDrawStyle(_pBody, GLU_FILL);
}

CylObject::CylObject(const CylObject &cylobj)
   : _R(cylobj._R)
   , _H(cylobj._H)
   , _XYZrZ(cylobj._XYZrZ)
   , _pBody(gluNewQuadric())
{
   // Drawable part
   gluQuadricDrawStyle(_pBody, GLU_FILL);
}

CylObject &CylObject::operator=(const CylObject &cylobj)
{
   if (this != &cylobj) {
      _R = cylobj._R;
      _H = cylobj._H;
      _XYZrZ = cylobj._XYZrZ;
      _pBody = gluNewQuadric();
      gluQuadricDrawStyle(_pBody, GLU_FILL);
   }
   return *this;
}

CylObject::~CylObject()
{
   gluDeleteQuadric(_pBody);
}

void CylObject::draw() const
{
   glPushMatrix();
   glColor3f(0.5, 0.5, 0.0);
   _XYZrZ.draw();
   gluCylinder(_pBody, _R, _R, _H, 10, 10);
   glPopMatrix();
}
