#include "Room.h"
#include "Log.h"
#include <sstream>

Room::Room()
   : m_corners()
{
   SET_FNAME("Room::Room()");
   m_corners.addVertex(CartVec(-3, -2, 0));
   m_corners.addVertex(CartVec(-3, 1, 0));
   m_corners.addVertex(CartVec(0, 1, 0));
   m_corners.addVertex(CartVec(0, 2, 0));
   m_corners.addVertex(CartVec(2, 2, 0));
   m_corners.addVertex(CartVec(2, -2, 0));
   m_corners.addVertex(CartVec(-3, -2, 0));
   m_corners.calcNormal();
   std::ostringstream msg;
   msg << m_corners;
   LOGD(msg.str());
}

void Room::draw() const
{
   glPushMatrix();
   glColor4f(0.6f, 0.2f, 0.2f, 1.0f); // line color
   double lw = 0;
   glGetDoublev(GL_LINE_WIDTH, &lw);
   glLineWidth(lw * 1.3);
   glBegin(GL_POLYGON);
   for (size_t i = 0; i < m_corners.getVertices().size(); ++i) {
      glVertex3f(m_corners[i].get_x(), m_corners[i].get_y(),
                 m_corners[i].get_z());
   }
   glVertex3f(m_corners[0].get_x(), m_corners[0].get_y(),
              m_corners[0].get_z());
   glEnd();
   glColor4f(0.15f, 0.15f, 0.15f, 0.7f); // line color
   glLineWidth(lw);
   glBegin(GL_LINES);
   for (size_t i = 0; i < m_corners.getVertices().size(); ++i) {
      glVertex3f(m_corners[i].get_x(), m_corners[i].get_y(),
                 m_corners[i].get_z());
      glVertex3f(m_corners[i].get_x(), m_corners[i].get_y(),
                 m_corners[i].get_z() + 0.5);
   }
   // glVertex3f(m_corners[0].x, m_corners[0].y, m_corners[0].z);
   glEnd();
   glLineWidth(lw);
   glPopMatrix();
}

CartVec Room::closestPointWall(int wallID, const CartVec &xyz) const
{
   return m_corners.getClosestPointToEdge(wallID, xyz);
}
