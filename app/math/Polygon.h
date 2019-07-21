#ifndef POLYGON_H
#define POLYGON_H

#include "CartVec.h"
#include "MathDef.h"

#include <cstddef>
#include <initializer_list>
#include <iosfwd>
#include <vector>

namespace math {

/// Represents a polygon: a number of coplanar line segments (edges),
/// each connected end to end to form a closed shape in 3D.
/// The vertices are represented by #CartVec objects in a std::vector.
/// Default assignment and copy ctor should work ok.
/// \short Represents a polygon in 3D space.
/// \todo Apply algorithms and Lambda functions.
class Polygon
{
   friend std::ostream &operator<<(std::ostream &os, const math::Polygon &rhs);

public:
   using minmaxXYZ_t = struct minmaxXYZ {
      double minX;
      double maxX;
      double minY;
      double maxY;
      double minZ;
      double maxZ;
   };

   /// Initializer list of vertices.
   /// math::Polygon p = { { 1, 2, 3 }, { 2, 3, 4 }, { 5, 7, 8 } };
   /// \pre Number of vertices >= 3 and these vertices are not collinear.
   Polygon(const std::initializer_list<CartVec> &cvlist);
   /// \pre Number of vertices >= 3 and these vertices are not collinear.
   explicit Polygon(const std::vector<CartVec> &vertices);

   /// Returns vertex by its index value.
   CartVec &operator[](const std::size_t index) { return vertices_[index]; }
   /// Returns vertex by its index value.
   const CartVec &operator[](const std::size_t index) const
   {
      return vertices_[index];
   }
   /// Adds new vertex to polygon, checks if polygon remains planar.
   /// @todo Add planarity check.
   void addVertex(const CartVec &vertex);
   /// @returns vertices.
   const std::vector<CartVec> &getVertices() const { return vertices_; }
   /// Calculates polygon normal.
   /// Uses the first, second, and third vertices to calculate the normal.
   /// @pre Number of vertices >= 3 and these vertices are not collinear.
   /// In this case, you can get the normal from the bounding rectangle.
   /// Use #setNormal() to explicitly set the normal.
   void calcNormal();
   /// @return Polygon normal.
   const CartVec &getNormal() const { return normal_; }
   /// Set normal explicitly.
   void setNormal(const CartVec &n) { normal_ = n; }
   /// Tests if this polygon is facing the specified point.
   bool isFacing(const CartVec &point) const;
   /// Get edge (pair of two vertices) by its index, starts at index 0.
   edge_t getEdge(std::size_t index) const;
   /// Get closest point on an edge identified by its index to point p.
   CartVec getClosestPointToEdge(std::size_t index, const CartVec &p) const;
   /// Calculates and returns minimal and maximal values x, y and z of all
   /// vertices. For bounding box calculations.
   minmaxXYZ_t getMinMaxXYZ() const;
   /// Translate polygon.
   Polygon &operator+=(const CartVec &rhs);
   /// Translate polygon.
   Polygon &operator-=(const CartVec &rhs);
   /// Rotate around X axes.
   /// @param angle rotation angle in degrees.
   void rotateAroundX(double angle);
   /// Rotate around Y axes.
   /// @param angle rotation angle in degrees.
   void rotateAroundY(double angle);
   /// Rotate around Z axes.
   /// @param angle rotation angle in degrees.
   void rotateAroundZ(double angle);
   /// Rotate around XYZ vector.
   /// @param angle rotation angle in degrees.
   void rotateAroundXYZ(const CartVec &xyz, double angle);
   /// Checks if point is inside the polygon.
   /// @todo Prepare for 3D.
   bool isInside(const CartVec &point) const;

private:
   /// Polygon vertices.
   std::vector<CartVec> vertices_;
   /// The normalized normal vector for the polygon.
   CartVec normal_;
};

} // namespace math

#endif // POLYGON_H
