#include "Circle.h"
#include "CartVec.h"

#include <iostream>
#include <iomanip>

namespace math {

std::ostream &operator<<(std::ostream &os, const Circle &rhs)
{
   os << std::setiosflags(std::ios::fixed) << std::setprecision(3) << "C["
      << rhs.center_ << ',' << std::setw(5) << rhs.radius_ << ']';
   return os;
}

bool operator==(const Circle &lhs, const Circle &rhs)
{
   auto comp = [](double d1, double d2) { return std::abs(d1 - d2) < 1E-8; };

   return (lhs.center_ == rhs.center_) and comp(lhs.radius_, rhs.radius_);
}

bool operator!=(const Circle &lhs, const Circle &rhs)
{
   return not(lhs == rhs);
}

Circle operator+(const Circle &lhs, const CartVec &rhs)
{
   return Circle{lhs} += rhs;
}

Circle operator-(const Circle &lhs, const CartVec &rhs)
{
   return Circle{lhs} -= rhs;
}

} // namespace math

math::Circle::Circle(const Point &center, double radius)
   : center_{center}
   , radius_{radius}
{
}

math::Circle::Circle(const Point &a, const Point &b)
   : center_{(a.get_x() + b.get_x()) / 2, (a.get_y() + b.get_y()) / 2}
   , radius_{a.distance(b) / 2}
{
}

math::Circle::Circle(const Point &a, const Point &b, const Point &c)
   : center_{}
   , radius_{-1}
{
   makeCircumcircle(a, b, c);
}

const math::Circle math::Circle::INVALID{Point::ORIGIN, -1.0};

math::Circle &math::Circle::operator+=(const CartVec &rhs)
{
   center_ += rhs;
   return *this;
}

math::Circle &math::Circle::operator-=(const CartVec &rhs)
{
   center_ -= rhs;
   return *this;
}

bool math::Circle::isInside(const Point &point) const
{
   return point.distance(center_) < radius_;
}

void math::Circle::makeCircumcircle(const Point &a, const Point &b,
                                    const Point &c)
{
   using namespace std;

   // Mathematical algorithm from Wikipedia: Circumscribed circle
   double ox = (min(min(a.get_x(), b.get_x()), c.get_x()) +
                max(min(a.get_x(), b.get_x()), c.get_x())) /
               2;
   double oy = (min(min(a.get_y(), b.get_y()), c.get_y()) +
                max(min(a.get_y(), b.get_y()), c.get_y())) /
               2;
   double ax = a.get_x() - ox, ay = a.get_y() - oy;
   double bx = b.get_x() - ox, by = b.get_y() - oy;
   double cx = c.get_x() - ox, cy = c.get_y() - oy;
   double d = (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) * 2;
   if (d == 0)
      *this = math::Circle::INVALID;
   double x =
      ((ax * ax + ay * ay) * (by - cy) + (bx * bx + by * by) * (cy - ay) +
       (cx * cx + cy * cy) * (ay - by)) /
      d;
   double y =
      ((ax * ax + ay * ay) * (cx - bx) + (bx * bx + by * by) * (ax - cx) +
       (cx * cx + cy * cy) * (bx - ax)) /
      d;
   Point p{ox + x, oy + y};
   double r = max(max(p.distance(a), p.distance(b)), p.distance(c));

   *this = {p, r};
}
