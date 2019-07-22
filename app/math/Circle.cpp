#include "Circle.h"
#include "CartVec.h"

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

Circle::Circle(const Point &center, double radius)
   : center_{center}
   , radius_{radius}
{
}

Circle &Circle::operator+=(const CartVec &rhs)
{
   center_ += rhs;
   return *this;
}

Circle &Circle::operator-=(const CartVec &rhs)
{
   center_ -= rhs;
   return *this;
}
