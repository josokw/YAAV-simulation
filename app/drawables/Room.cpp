#include "Room.h"
#include "Log.h"

#include <sstream>

Room::Room()
   : corners_{{-3, -2, 0}, {-3, 1, 0}, {0, 1, 0},
              {0, 2, 0},   {2, 2, 0},  {2, -2, 0}}
{
   SET_FNAME("Room::Room()");
   corners_.calcNormal();
   std::ostringstream msg;
   msg << corners_;
   LOGD(msg.str());
}

void Room::draw() const
{
   glPushMatrix();
   glColor4f(0.6f, 0.2f, 0.2f, 1.0f); // line color
   double lw = 0.0;
   glGetDoublev(GL_LINE_WIDTH, &lw);
   glLineWidth(lw * 1.4);
   glBegin(GL_POLYGON);
   for (const auto &corner : corners_.getVertices()) {
      glVertex3f(corner.get_x(), corner.get_y(), corner.get_z());
   }
   glVertex3f(corners_[0].get_x(), corners_[0].get_y(), corners_[0].get_z());
   glEnd();
   glColor4f(0.15f, 0.15f, 0.15f, 0.7f); // line color
   glLineWidth(lw);
   glBegin(GL_LINES);
   for (const auto &corner : corners_.getVertices()) {
      glVertex3f(corner.get_x(), corner.get_y(), corner.get_z());
      glVertex3f(corner.get_x(), corner.get_y(), corner.get_z() + 0.5);
   }
   glEnd();
   glLineWidth(lw);
   glPopMatrix();
}

math::Point Room::closestPointWall(int wallID, const math::Point &xyz) const
{
   return corners_.getClosestPointToEdge(wallID, xyz);
}
