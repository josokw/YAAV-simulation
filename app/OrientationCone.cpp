#include "OrientationCone.h"
#include "math/MathDef.h"

const OrientationCone OrientationCone::OcX(1, 0, 0, XYZrZ(1, 0, 0));
const OrientationCone OrientationCone::OcY(0, 1, 0, XYZrZ(0, 1, 0));
const OrientationCone OrientationCone::OcZ(0, 0, 1, XYZrZ(0, 0, 1));

OrientationCone operator*(const OrientationCone &lhs, double rhs)
{
   return OrientationCone(
      lhs.m_r, lhs.m_g, lhs.m_b,
      XYZrZ(lhs.m_XYZrZ.position * rhs, lhs.m_XYZrZ.Rz));
}

OrientationCone operator*(double lhs, const OrientationCone &rhs)
{
   return rhs * lhs;
}

OrientationCone::OrientationCone(double r, double g, double b,
                                 const XYZrZ &xyzRz)
   : Drawable()
   , m_r(r)
   , m_g(g)
   , m_b(b)
   , m_XYZrZ(xyzRz)
   , m_size(xyzRz.length())
   , m_pBody(gluNewQuadric())
{
   gluQuadricDrawStyle(m_pBody, GLU_FILL);
}

OrientationCone::OrientationCone(const OrientationCone &ocone)
   : Drawable()
   , m_r(ocone.m_r)
   , m_g(ocone.m_g)
   , m_b(ocone.m_b)
   , m_XYZrZ(ocone.m_XYZrZ)
   , m_size(m_XYZrZ.length())
   , m_pBody(gluNewQuadric())
{
   gluQuadricDrawStyle(m_pBody, GLU_FILL);
}

OrientationCone::~OrientationCone()
{
   gluDeleteQuadric(m_pBody);
}

void OrientationCone::draw() const
{
   double yaw;
   double pitch;

   if (fabs((m_XYZrZ.position.get_x()) < 1e-4 &&
            fabs(m_XYZrZ.position.get_z()) < 1e-4)) {
      yaw = 0.0;
   } else {
      yaw = atan2(m_XYZrZ.position.get_x(), m_XYZrZ.position.get_z());
   }
   pitch =
      -atan2(m_XYZrZ.position.get_y(),
             sqrt(m_XYZrZ.position.get_x() * m_XYZrZ.position.get_x() +
                  m_XYZrZ.position.get_z() * m_XYZrZ.position.get_z()));
   glPushMatrix();
   glColor3f(m_r, m_g, m_b);
   glBegin(GL_LINES);
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(m_XYZrZ.position.get_x(), m_XYZrZ.position.get_y(),
              m_XYZrZ.position.get_z());
   glEnd();
   glTranslatef(m_XYZrZ.position.get_x() * 0.66,
                m_XYZrZ.position.get_y() * 0.66,
                m_XYZrZ.position.get_z() * 0.66);
   glRotatef(math::toDegrees(yaw), 0.0, 1.0, 0.0);
   glRotatef(math::toDegrees(pitch), 1.0, 0.0, 0.0);
   glRotatef(m_XYZrZ.Rz, 0.0, 0.0, 1.0);
   gluCylinder(m_pBody, m_size / 20, 0, m_size / 3, 10, 10);
   glPopMatrix();
}
