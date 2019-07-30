#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

#include <cmath>
#include <tuple>

class CartVec;

namespace math {

/// Represents a circle (center point and radius).
/// Can be translated by a vector (CartVec).
class Circle
{
   /// Output format: C[P[x,y,z],r]
   friend std::ostream &operator<<(std::ostream &os, const Circle &rhs); 
   friend bool operator==(const Circle &lhs, const Circle &rhs);
   friend bool operator!=(const Circle &lhs, const Circle &rhs);
   /// Translate: c1 = c2 + v
   friend Circle operator+(const Circle &lhs, const CartVec &rhs);
   /// TranslateL c1 = c2 - v
   friend Circle operator-(const Circle &lhs, const CartVec &rhs);

public:
   static const Circle INVALID;
   static double epsCOMPARE;
   static double epsMULTIPLY;

   Circle() = default;
   Circle(const Point &center, double radius = 1.0);
   /// Create circle through 2 points, for z = 0.
   /// \pre z == 0.0 and a != b
   Circle(const Point &a, const Point &b);
   /// Create circle through 3 points, for z = 0.
   /// \pre z == 0.0 and a, b and c are not collinear.
   Circle(const Point &a, const Point &b, const Point &c);

   const Point &getCenter() const { return center_; }
   double getRadius() const { return radius_; }
   std::tuple<Point, double> getCenterRadius() const
   {
      return {center_, radius_};
   }
   bool isNotValid() const { return radius_ < 0.0; }
   /// Translation: c += cv
   Circle &operator+=(const CartVec &rhs);
   /// Translation: c -= cv
   Circle &operator-=(const CartVec &rhs);

   bool isInside(const Point &point) const;
   /// Calculates area.
   double area() const { return 2 * M_PI * radius_; }

private:
   Point center_{0.0, 0.0, 0.0};
   double radius_{1.0};

   void makeCircumcircle(const Point &a, const Point &b, const Point &c);
};

} // namespace math

#endif // CIRCLE_H
