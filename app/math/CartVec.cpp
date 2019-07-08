#include "CartVec.h"
#include "MathDef.h"

#include <iomanip>
#include <ios>
#include <iostream>

double CartVec::eps{1E-8};
const CartVec CartVec::ZERO{0.0, 0.0, 0.0};
const CartVec CartVec::UNIT_X{1.0, 0.0, 0.0};
const CartVec CartVec::UNIT_Y{0.0, 1.0, 0.0};
const CartVec CartVec::UNIT_Z{0.0, 0.0, 1.0};

CartVec::CartVec(double x, double y, double z)
   : x_{x}
   , y_{y}
   , z_{z}
{
}

bool operator==(const CartVec &lhs, const CartVec &rhs)
{
   auto comp = [](double d1, double d2) {
      return fabs(d1 - d2) < CartVec::eps;
   };

   return comp(lhs.x_, rhs.x_) and comp(lhs.y_, rhs.y_) and
          comp(lhs.z_, rhs.z_);
}

bool operator!=(const CartVec &lhs, const CartVec &rhs)
{
   return not(lhs == rhs);
}

CartVec operator+(const CartVec &lhs, const CartVec &rhs)
{
   CartVec temp(lhs);
   return temp += rhs;
}

CartVec operator-(const CartVec &lhs, const CartVec &rhs)
{
   CartVec temp(lhs);
   return temp -= rhs;
}

CartVec operator*(double lhs, const CartVec &rhs)
{
   CartVec temp(rhs);
   return temp *= lhs;
}

CartVec operator*(const CartVec &lhs, double rhs)
{
   CartVec temp(lhs);
   return temp *= rhs;
}

CartVec operator/(const CartVec &lhs, double rhs)
{
   CartVec temp(lhs);
   return temp /= rhs;
}

double CartVec::distance(const CartVec &cv) const
{
   return std::sqrt((x_ - cv.x_) * (x_ - cv.x_) + (y_ - cv.y_) * (y_ - cv.y_) +
                    (z_ - cv.z_) * (z_ - cv.z_));
}

double CartVec::angle(const CartVec &v) const
{
   auto comp = [](double d1, double d2) {
      return fabs(d1 - d2) < CartVec::eps;
   };
   // Construct the plane containing v and *this;
   // a local CS is constructed with xx in direction *this
   // yy generates other component of v
   // then atan2 for angle calculation is called.
   double xxL = length();

   if (comp(xxL, 0.0)) {
      return 0;
   }
   CartVec zz{this->cross(v)}; // z-Axis
   double zzL = zz.length();
   if (comp(zzL, 0.0)) {
      // v can coincide with *this or can point in the opposite direction!
      if (-v == *this) {
         return M_PI;
      }
      return 0;
   }
   CartVec xx{(*this) / xxL}; // x-Axis
   zz /= zzL;
   // now zz and xx are orthonormal to each other.
   CartVec yy{zz.cross(xx)}; // y-Axis
   return atan2(yy.dot(v), xx.dot(v));
}

void CartVec::rotateAroundZ(double cosPhi, double sinPhi)
{
   double xtemp = x_;
   x_ = cosPhi * x_ - sinPhi * y_;
   y_ = sinPhi * xtemp + cosPhi * y_;
}

void CartVec::rotateAroundY(const double cosPhi, const double sinPhi)
{
   double xtemp = x_;
   x_ = cosPhi * x_ + sinPhi * z_;
   z_ = -sinPhi * xtemp + cosPhi * z_;
}

void CartVec::rotateAroundX(double cosPhi, double sinPhi)
{
   double ytemp = y_;
   y_ = cosPhi * y_ - sinPhi * z_;
   z_ = sinPhi * ytemp + cosPhi * z_;
}

void CartVec::rotateAround(const CartVec &Axis, double cosPhi, double sinPhi)
{
   auto comp = [](double d1, double d2) {
      return fabs(d1 - d2) < CartVec::eps;
   };
   // An arbitrarily rotation around Axis.
   // Implemented by constructing a new local CS
   // In this CS Axis becomes zz and xx will span the orthogonal
   // component of xx. yy is constructed by a cross product.
   double axisL{Axis.length()};
   if (comp(axisL, 0.0)) {
      return; // a rotation around zero-CartVec is *this
   }

   CartVec zz{Axis};
   zz.normalize();    // zz is unit-length
   CartVec xx{*this}; // xx and zz are NOT orthogonal !!
   CartVec yy{zz.cross(xx)};
   double yyL{yy.length()};

   if (comp(yyL, 0.0)) {
      // now we have 2 possibilities
      //	 either the two CartVecs are dependent
      //	 or one of them is zero.
      // Best thing to do: return *this
      return;
   }
   yy /= yyL;
   // now zz and yy are orthonormal to each other.
   xx = yy.cross(zz);
   // so now we have complete orthonormal set
   CartVec NCS{dot(xx), dot(yy), dot(zz)}; // New Coordinate System

   NCS.rotateAroundZ(cosPhi, sinPhi); // do the rotation in New CS
   *this = xx * NCS.x_ + yy * NCS.y_ + zz * NCS.z_;
}

std::ostream &operator<<(std::ostream &os, const CartVec &rhs)
{
   os << std::setiosflags(std::ios::fixed) << std::setprecision(3) << '['
      << std::setw(5) << rhs.x_ << ',' << std::setw(5) << rhs.y_ << ','
      << std::setw(5) << rhs.z_ << ']';
   return os;
}

std::istream &operator>>(std::istream &is, CartVec &rhs)
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
      rhs = CartVec(x, y, z);
   }
   return is; // Client code should check state of 'is'
}
