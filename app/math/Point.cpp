#include "Point.h"
#include "CartVec.h"

#include <cmath>
#include <iomanip>

namespace math {

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
   os << std::setiosflags(std::ios::fixed) << std::setprecision(3) << "P["
      << std::setw(5) << rhs.x_ << ',' << std::setw(5) << rhs.y_ << ','
      << std::setw(5) << rhs.z_ << ']';
   return os;
}

std::istream &operator>>(std::istream &is, Point &rhs)
{
   char o = '\0';  // '['
   char c1 = '\0'; // ','
   char c2 = '\0'; // ','
   char c = '\0';  // ']'
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;

   is.clear();
   is >> std::ws >> o >> x >> std::ws >> c1 >> y >> std::ws >> c2 >> z >>
      std::ws >> c;
   if ((o != '[') || (c1 != ',') || (c2 != ',') || (c != ']')) {
      is.setstate(std::ios::failbit);
   }
   // Only if everything is ok, output parameter rhs will be changed.
   if (is) {
      rhs = {x, y, z};
   }
   return is; // Client code should check state of 'is'
}

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

math::CartVec operator-(const Point &lhs, const Point &rhs)
{
   return {lhs.get_x() - rhs.get_x(), lhs.get_y() - rhs.get_y(),
           lhs.get_z() - rhs.get_z()};
}

Point operator+(const Point &lhs, const math::CartVec &rhs)
{
   return {lhs.get_x() + rhs.get_x(), lhs.get_y() + rhs.get_y(),
           lhs.get_z() + rhs.get_z()};
}

Point operator-(const Point &lhs, const math::CartVec &rhs)
{
   return {lhs.get_x() - rhs.get_x(), lhs.get_y() - rhs.get_y(),
           rhs.get_z() - lhs.get_z()};
}

const Point Point::ORIGIN{0.0, 0.0, 0.0};
double Point::eps{math::CartVec::eps};

Point::Point(double x, double y, double z)
   : x_{x}
   , y_{y}
   , z_{z}
{
}

Point &Point::operator+=(const math::CartVec &rhs)
{
   x_ += rhs.get_x();
   y_ += rhs.get_y();
   z_ += rhs.get_z();

   return *this;
}

Point &Point::operator-=(const math::CartVec &rhs)
{
   x_ -= rhs.get_x();
   y_ -= rhs.get_y();
   z_ -= rhs.get_z();

   return *this;
}

void Point::rotateAroundZ(double cosPhi, double sinPhi)
{
   double xtemp{x_};
   x_ = cosPhi * x_ - sinPhi * y_;
   y_ = sinPhi * xtemp + cosPhi * y_;
}

void Point::rotateAroundY(const double cosPhi, const double sinPhi)
{
   double xtemp = x_;
   x_ = cosPhi * x_ + sinPhi * z_;
   z_ = -sinPhi * xtemp + cosPhi * z_;
}

void Point::rotateAroundX(double cosPhi, double sinPhi)
{
   double ytemp = y_;
   y_ = cosPhi * y_ - sinPhi * z_;
   z_ = sinPhi * ytemp + cosPhi * z_;
}

// void Point::rotateAround(const CartVec &Axis, double cosPhi, double sinPhi)
// {
//    auto comp = [](double d1, double d2) {
//       return std::abs(d1 - d2) < CartVec::eps;
//    };
//    // An arbitrarily rotation around Axis.
//    // Implemented by constructing a new local CS
//    // In this CS Axis becomes zz and xx will span the orthogonal
//    // component of xx. yy is constructed by a cross product.
//    double axisL{Axis.length()};
//    if (comp(axisL, 0.0)) {
//       return; // a rotation around zero-CartVec is *this
//    }

//    CartVec zz{Axis};
//    zz.normalize();    // zz is unit-length
//    CartVec xx{*this}; // xx and zz are NOT orthogonal !!
//    CartVec yy{zz.cross(xx)};
//    double yyL{yy.length()};

//    if (comp(yyL, 0.0)) {
//       // now we have 2 possibilities
//       //	 either the two CartVecs are dependent
//       //	 or one of them is zero.
//       // Best thing to do: return *this
//       return;
//    }
//    yy /= yyL;
//    // now zz and yy are orthonormal to each other.
//    xx = yy.cross(zz);
//    // so now we have complete orthonormal set
//    CartVec NCS{dot(xx), dot(yy), dot(zz)}; // New Coordinate System

//    NCS.rotateAroundZ(cosPhi, sinPhi); // do the rotation in New CS
//    *this = xx * NCS.x_ + yy * NCS.y_ + zz * NCS.z_;
// }

double Point::distance(const Point &pnt) const
{
   return std::sqrt((x_ - pnt.x_) * (x_ - pnt.x_) +
                    (y_ - pnt.y_) * (y_ - pnt.y_) +
                    (z_ - pnt.z_) * (z_ - pnt.z_));
}

} // namespace math
