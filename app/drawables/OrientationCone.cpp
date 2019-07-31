#include "OrientationCone.h"
#include "MathDef.h"

const OrientationCone OrientationCone::OcX({1, 0, 0}, {2, 0, 0}, {1, 0, 0});
const OrientationCone OrientationCone::OcY({0, 1, 0}, {2, 0, 0}, {0, 1, 0});
const OrientationCone OrientationCone::OcZ({0, 0, 1}, {2, 0, 0}, {0, 0, 1});

OrientationCone operator*(const OrientationCone &lhs, double rhs)
{
   return {lhs.rgb_, lhs.position_, lhs.orientation_ * rhs};
}

OrientationCone operator*(double lhs, const OrientationCone &rhs)
{
   return rhs * lhs;
}

OrientationCone::OrientationCone(const std::array<float, 3> &rgb,
                                 const math::Point &position,
                                 const math::CartVec &orientation)
   : Drawable()
   , rgb_{rgb}
   , position_{position}
   , orientation_{orientation}
   , pBody_(gluNewQuadric())
{
   gluQuadricDrawStyle(pBody_, GLU_FILL);
}

OrientationCone::OrientationCone(const OrientationCone &ocone)
   : Drawable{}
   , rgb_{ocone.rgb_}
   , position_{ocone.position_}
   , orientation_{ocone.orientation_}
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

   if ((std::abs((orientation_.get_x()) < 1e-4) and
        (std::abs(orientation_.get_z()) < 1e-4))) {
      yaw = 0.0;
   } else {
      yaw = atan2(orientation_.get_x(), orientation_.get_z());
   }
   pitch = -atan2(orientation_.get_y(),
                  sqrt(orientation_.get_x() * orientation_.get_x() +
                       orientation_.get_z() * orientation_.get_z()));
   glPushMatrix();
   glColor3f(rgb_[0], rgb_[1], rgb_[2]);
   glBegin(GL_LINES);
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(orientation_.get_x(), orientation_.get_y(), orientation_.get_z());
   glEnd();
   glTranslatef(orientation_.get_x() * 0.66, orientation_.get_y() * 0.66,
                orientation_.get_z() * 0.66);

   glRotatef(math::toDegrees(yaw), 0.0, 1.0, 0.0);
   glRotatef(math::toDegrees(pitch), 1.0, 0.0, 0.0);

   auto size{orientation_.length()};
   gluCylinder(pBody_, size / 25, 0, size / 2, 10, 10);

   //glTranslatef(position_.get_x(), position_.get_y(), position_.get_z());

   glPopMatrix();
}
