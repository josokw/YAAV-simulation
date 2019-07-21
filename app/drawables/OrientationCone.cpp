#include "OrientationCone.h"
#include "MathDef.h"

const OrientationCone OrientationCone::OcX(1, 0, 0, XYZrZ{1, 0, 0});
const OrientationCone OrientationCone::OcY(0, 1, 0, XYZrZ{0, 1, 0});
const OrientationCone OrientationCone::OcZ(0, 0, 1, XYZrZ{0, 0, 1});

OrientationCone operator*(const OrientationCone &lhs, double rhs)
{
   return {lhs.red_, lhs.green_, lhs.blue_,
           XYZrZ(lhs.XYZrZ_.position * rhs, lhs.XYZrZ_.Rz)};
}

OrientationCone operator*(double lhs, const OrientationCone &rhs)
{
   return rhs * lhs;
}

OrientationCone::OrientationCone(double red, double green, double blue,
                                 const XYZrZ &xyzRz)
   : Drawable()
   , red_(red)
   , green_(green)
   , blue_(blue)
   , XYZrZ_(xyzRz)
   , size_(xyzRz.length())
   , pBody_(gluNewQuadric())
{
   gluQuadricDrawStyle(pBody_, GLU_FILL);
}

OrientationCone::OrientationCone(const OrientationCone &ocone)
   : Drawable()
   , red_(ocone.red_)
   , green_(ocone.green_)
   , blue_(ocone.blue_)
   , XYZrZ_(ocone.XYZrZ_)
   , size_(XYZrZ_.length())
   , pBody_(gluNewQuadric())
{
   gluQuadricDrawStyle(pBody_, GLU_FILL);
}

OrientationCone::~OrientationCone()
{
   gluDeleteQuadric(pBody_);
}

void OrientationCone::draw() const
{
   double yaw;
   double pitch;

   if ((std::abs((XYZrZ_.position.get_x()) < 1e-4) and
        (std::abs(XYZrZ_.position.get_z()) < 1e-4))) {
      yaw = 0.0;
   } else {
      yaw = atan2(XYZrZ_.position.get_x(), XYZrZ_.position.get_z());
   }
   pitch = -atan2(XYZrZ_.position.get_y(),
                  sqrt(XYZrZ_.position.get_x() * XYZrZ_.position.get_x() +
                       XYZrZ_.position.get_z() * XYZrZ_.position.get_z()));
   glPushMatrix();
   glColor3f(red_, green_, blue_);
   glBegin(GL_LINES);
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(XYZrZ_.position.get_x(), XYZrZ_.position.get_y(),
              XYZrZ_.position.get_z());
   glEnd();
   glTranslatef(XYZrZ_.position.get_x() * 0.66, XYZrZ_.position.get_y() * 0.66,
                XYZrZ_.position.get_z() * 0.66);
   glRotatef(math::toDegrees(yaw), 0.0, 1.0, 0.0);
   glRotatef(math::toDegrees(pitch), 1.0, 0.0, 0.0);
   glRotatef(XYZrZ_.Rz, 0.0, 0.0, 1.0);
   gluCylinder(pBody_, size_ / 20, 0, size_ / 3, 10, 10);
   glPopMatrix();
}
