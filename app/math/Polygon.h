#ifndef POLYGON_H
#define POLYGON_H

#include "CartVec.h"
#include "Circle.h"
#include "Edge.h"
#include "Point.h"

#include <initializer_list>
#include <vector>

namespace math {

/// Represents a polygon: a number of coplanar line segments (edges),
/// each connected end to end to form a closed shape in 3D.
/// The vertices are represented by #Point objects in a std::vector.
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
   /// math::Polygon p = { { 1, 2}, { 2, 3}, { 5, 7} };
   /// \pre Number of vertices >= 3 and these vertices are not collinear.
   Polygon(const std::initializer_list<Point> &cvlist);
   /// \pre Number of vertices >= 3 and these vertices are not collinear.
   explicit Polygon(const std::vector<Point> &vertices);

   /// Returns vertex by its index value.
   Point &operator[](const std::size_t index) { return vertices_[index]; }
   /// Returns vertex by its index value.
   const Point &operator[](const std::size_t index) const
   {
      return vertices_[index];
   }
   /// Adds new vertex to polygon, checks if polygon remains planar.
   /// \todo Add planarity check.
   void addVertex(const Point &vertex);
   /// \returns vertices.
   const std::vector<Point> &getVertices() const { return vertices_; }
   /// Calculates polygon normal.
   /// Uses the first, second, and third vertices to calculate the normal.
   /// @pre Number of vertices >= 3 and these vertices are not collinear.
   /// In this case, you can get the normal from the bounding rectangle.
   /// Use #setNormal() to explicitly set the normal.
   void calcNormal();
   /// \return Polygon normal.
   const CartVec &getNormal() const { return normal_; }
   /// Set normal explicitly.
   /// \todo Necessary function?
   void setNormal(const CartVec &n) { normal_ = n; }
   /// Tests if this polygon is facing the specified point.
   bool isFacing(const Point &point) const;
   /// Get edge (pair of two vertices) by its index, starts at index 0.
   math::Edge getEdge(std::size_t index) const;
   /// Get closest point on an edge identified by its index to point p.
   Point getClosestPointToEdge(std::size_t index, const Point &p) const;
   /// Calculates and returns minimal and maximal values x, y and z of all
   /// vertices. For bounding box calculations.
   minmaxXYZ_t getMinMaxXYZ() const;
   //
   Circle getSmallestEnclosingCircle() const { return smallestEnclosingCircle_; }
   /// Translate: p += cv
   Polygon &operator+=(const CartVec &rhs);
   /// Translate: p -= cv
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
   void rotateAroundXYZ(const Point &xyz, double angle);
   /// Checks if point is inside the polygon.
   /// \todo Prepare for 3D.
   bool isInside(const Point &point) const;
   /// Checks if all points are inside the polygon.
   bool isInside(const std::vector<Point> &points) const;

private:
   /// Polygon vertices.
   std::vector<Point> vertices_;
   /// The normalized normal vector for the polygon.
   CartVec normal_;
   /// Contains smmalles enclosing circle.
   /// \info Calculations based on: Project Nayuki.
   mutable math::Circle smallestEnclosingCircle_;

   /// No boundary points known
   void makeSmallestEnclosingCircle() const;
   /// One boundary point known
   math::Circle
   makeSmallestEnclosingCircleOnePoint(const std::vector<Point> &points,
                                       size_t end, const Point &point) const;
   /// Two boundary points known
   math::Circle
   makeSmallestEnclosingCircleTwoPoints(const std::vector<Point> &points,
                                        size_t end, const Point &p,
                                        const Point &q) const;
};

} // namespace math

#endif // POLYGON_H
