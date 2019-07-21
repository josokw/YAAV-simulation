#include "Point.h"
#include "CartVec.h"

#include <cmath>

bool operator==(const Point &lhs, const Point &rhs)
{
   auto comp = [](double d1, double d2) {
      return std::abs(d1 - d2) < Point::eps;
   };

   return comp(lhs.x_, rhs.x_) and comp(lhs.y_, rhs.y_) and
          comp(lhs.z_, rhs.z_);
}

bool operator!=(const Point &lhs, const Point &rhs)
{
   return not(lhs == rhs);
}

CartVec operator-(const Point &lhs, const Point &rhs)
{
   return {rhs.get_x() - lhs.get_x(), rhs.get_y() - lhs.get_y(),
           rhs.get_z() - lhs.get_z()};
}

Point operator+(const Point &lhs, const CartVec &rhs)
{
   return {lhs.get_x() + rhs.get_x(), lhs.get_y() + rhs.get_y(),
           lhs.get_z() + rhs.get_z()};
}

Point operator-(const Point &lhs, const CartVec &rhs)
{
   return {lhs.get_x() - rhs.get_x(), lhs.get_y() - rhs.get_y(),
           rhs.get_z() - lhs.get_z()};
}

const Point Point::ORIGIN{0.0, 0.0, 0.0};
double Point::eps{CartVec::eps};

Point::Point(double x, double y, double z)
   : x_{x}
   , y_{y}
   , z_{z}
{
}

Point &Point::operator+=(const CartVec &rhs)
{
   x_ += rhs.get_x();
   y_ += rhs.get_y();
   z_ += rhs.get_z();

   return *this;
}

Point &Point::operator-=(const CartVec &rhs)
{
   x_ -= rhs.get_x();
   y_ -= rhs.get_y();
   z_ -= rhs.get_z();

   return *this;
}
