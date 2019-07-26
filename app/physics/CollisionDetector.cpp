#include "CollisionDetector.h"
#include "Log.h"

#include <sstream>

bool physics::CollisionDetector::isColliding(const math::circle_t &c,
                                             const math::Polygon &p)
{
   SET_FNAME("physics::CollisionDetector::isColliding(circle, polygon)");
   collisionPoints_.clear();
   const std::vector<Point> &vertices(p.getVertices());
   size_t nCollisions = 0;
   // {
   //    std::ostringstream msg;
   //    msg << p;
   //    LOGD(msg.str());
   // }
   for (size_t vertexID = 0; vertexID < vertices.size(); ++vertexID) {
      Point closestPoint(p.getClosestPointToEdge(vertexID, c.m));
      {
         std::ostringstream msg;
         msg << "closestPoint = " << closestPoint;
         LOGD(msg.str());
      }
      double distance = closestPoint.distance(c.m);
      if (distance <= c.r) {
         ++nCollisions;
         collisionPoints_.push_back(closestPoint);
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
   collisionPoints_.clear();
   CartVec delta{c2.m - c1.m};
   if (delta.length() <= (c1.r + c2.r)) {
      Point collisionPoint{c1.m + delta * ((c1.r + c2.r) / c1.r)};
      collisionPoints_.push_back(collisionPoint);
      std::ostringstream msg;
      msg << "WCS collision point: " << collisionPoint;
      LOGD(msg.str());
      return true;
   }
   return false;
}
