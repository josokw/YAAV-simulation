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
   friend bool operator==(const Circle &lhs, const Circle &rhs);
   friend bool operator!=(const Circle &lhs, const Circle &rhs);
   /// Translate: c1 = c2 + v
   friend Circle operator+(const Circle &lhs, const CartVec &rhs);
   /// TranslateL c1 = c2 - v
   friend Circle operator-(const Circle &lhs, const CartVec &rhs);

public:
   static double eps;

   Circle() = default;
   Circle(const Point &center, double radius = 1.0);

   const Point &getCenter() const { return center_; }
   double getRadius() const { return radius_; }
   std::tuple<Point, double> getCenterRadius() const
   {
      return {center_, radius_};
   }
   /// Translation: c += cv
   Circle &operator+=(const CartVec &rhs);
   /// Translation: c -= cv
   Circle &operator-=(const CartVec &rhs);
   /// Calculates area.
   double area() const { return 2 * M_PI * radius_; }

private:
   Point center_{0.0, 0.0, 0.0};
   double radius_{1.0};
};

} // namespace math

#endif // CIRCLE_H
