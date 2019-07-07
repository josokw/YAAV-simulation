#include "Point.h"
#include "CartVec.h"

#include <iostream>

CartVec operator-(const Point &lhs, const Point &rhs)
{
   return {rhs.get_x() - lhs.get_x(), rhs.get_y() - lhs.get_y(),
           rhs.get_z() - lhs.get_z()};
}

Point operator+(const Point &lhs, const CartVec &rhs)
{
   return Point{lhs.get_x() + rhs.get_x(), lhs.get_y() + rhs.get_y(),
                lhs.get_z() + rhs.get_z()};
}

Point operator-(const Point &lhs, const CartVec &rhs)
{
   return {lhs.get_x() - rhs.get_x(), lhs.get_y() - rhs.get_y(),
           rhs.get_z() - lhs.get_z()};
}

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