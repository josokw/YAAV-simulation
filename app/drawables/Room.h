#ifndef ROOM_H
#define ROOM_H

#include "Drawable.h"
#include "Polygon.h"
#include "Point.h"

#include <vector>

class Point;

/// Room contains a number of corners (Z-values must be 0) represented by a
/// #Polygon. Every pair of consecutive corners represents a wall.
/// \short Room containing a number of walls.
class Room : public Drawable
{
public:
   Room();
   ~Room() override = default;

   void draw() const override;
   /// Returns collision shape.
   const math::Polygon &getCollisionShape() const { return corners_; }
   const std::vector<Point> &getCorners() const
   {
      return corners_.getVertices();
   }
   /// Checks if point is in the room. Z-value is ignored!
   bool isInside(const Point &point) const { return corners_.isInside(point); }
   math::Polygon::minmaxXYZ_t getMinMaxXYZ() const
   {
      return corners_.getMinMaxXYZ();
   }

private:
   /// Last corner must equals first corner.
   math::Polygon corners_;

public:
   Point closestPointWall(int wallID, const Point &xyz) const;
};

#endif // ROOM_H
