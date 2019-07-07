#ifndef ROOM_H
#define ROOM_H

#include "Drawable.h"
#include "math/Polygon.h"
#include <vector>

/// Room contains a number of corners (Z-values must be 0) represented by a
/// #Polygon. Every pair of consecutive corners represents a wall.
/// @short Room containing a number of walls.
class Room : public Drawable
{
public:
   Room();
   virtual ~Room() = default;

   virtual void draw() const;
   /// Returns collision shape.
   const math::Polygon &getCollisionShape() const { return m_corners; }
   const std::vector<CartVec> &getCorners() const
   {
      return m_corners.getVertices();
   }
   /// Checks if point is in the room. Z-value is ignored!
   bool isInside(const CartVec &point) const
   {
      return m_corners.isInside(point);
   }
   math::minmaxXYZ_t getMinMaxXYZ() const
   {
      return m_corners.getMinMaxXYZ();
   }

private:
   /// Last corner must equals first corner.
   math::Polygon m_corners;

public:
   CartVec closestPointWall(int wallID, const CartVec &xyz) const;
};

#endif // ROOM_H
