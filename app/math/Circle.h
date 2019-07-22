#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

#include <cmath>
#include <tuple>

class CartVec;

/// Represents a circle. Can be translated by a vector (CartVec).
class Circle
{
   friend bool operator==(const Circle &lhs, const Circle &rhs);
   friend bool operator!=(const Circle &lhs, const Circle &rhs);
   /// Translate circle (lhs) by vector (rhs)
   friend Circle operator+(const Circle &lhs, const CartVec &rhs);
   /// Translate circle (lhs) by -vector (rhs)
   friend Circle operator-(const Circle &lhs, const CartVec &rhs);

public:
   static double eps;

   Circle() = default;
   Circle(const Point &center, double radius = 1.0);

   const Point &getCenter() const { return center_; }
   double getRadius() const { return radius_; }
   std::tuple<Point, double> get() const { return {center_, radius_}; }

   Circle &operator+=(const CartVec &rhs);
   Circle &operator-=(const CartVec &rhs);
   double area() const { return 2 * M_PI * radius_; }

private:
   Point center_{0.0, 0.0, 0.0};
   double radius_{1.0};
};

#endif // CIRCLE_H
