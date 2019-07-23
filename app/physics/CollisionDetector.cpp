#include "CollisionDetector.h"
#include "Log.h"

#include <sstream>

bool physics::CollisionDetector::isColliding(const math::circle_t &c,
                                             const math::Polygon &p)
{
   SET_FNAME("physics::CollisionDetector::isColliding(circle, polygon)");
   m_collisionPoints.clear();
   std::vector<CartVec> vertices(p.getVertices());
   size_t nCollisions = 0;
   for (size_t vertexID = 0; vertexID < vertices.size(); ++vertexID) {
      CartVec closestPoint(p.getClosestPointToEdge(vertexID, c.m));
      double distance = closestPoint.distance(c.m);
      if (distance <= c.r) {
         ++nCollisions;
         m_collisionPoints.push_back(closestPoint);
         std::ostringstream msg;
         msg << "#" << nCollisions << " vertexID = " << vertexID
             << " WCS: " << closestPoint;
         LOGD(msg.str());
      }
   }
   return nCollisions > 0;
}

bool physics::CollisionDetector::isColliding(const math::circle_t &c1,
                                             const math::circle_t &c2)
{
   SET_FNAME("physics::CollisionDetector::isColliding(circle, circle)");
   m_collisionPoints.clear();
   CartVec delta(c2.m - c1.m);
   if (delta.length() <= (c1.r + c2.r)) {
      CartVec collisionPoint(c1.m + delta * ((c1.r + c2.r) / c1.r));
      m_collisionPoints.push_back(collisionPoint);
      std::ostringstream msg;
      msg << "WCS: " << collisionPoint;
      LOGD(msg.str());
      return true;
   }
   return false;
}
