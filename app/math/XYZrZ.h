#ifndef XYZRZ_H
#define XYZRZ_H

#include "CartVec.h"
#include "Drawable.h"
#include "MathDef.h"

#include <cmath>
#include <iostream>

/// Represents the combination of a position represented by a #CartVec
/// [x,y,z] and a rotation around de Z-axis #Rz [degrees].
/// 4 DOF: [[x, y, z], Rz].
class XYZrZ : public Drawable
{
   friend std::ostream &operator<<(std::ostream &os, const XYZrZ &rhs);
   friend XYZrZ operator+(const XYZrZ &lhs, const XYZrZ &rhs);
   friend XYZrZ operator-(const XYZrZ &lhs, const XYZrZ &rhs);
   friend XYZrZ operator*(const XYZrZ &lhs, double rhs);
   friend XYZrZ operator+(const XYZrZ &lhs, const CartVec &rhs);
   friend XYZrZ operator-(const XYZrZ &lhs, const CartVec &rhs);
   /// [[x,y,z], rZ] + a => [[x,y,z], rZ + a]
   friend XYZrZ operator+(const XYZrZ &lhs, double rhs);
   /// [[x,y,z], rZ] - a => [[x,y,z], rZ - a]
   friend XYZrZ operator-(const XYZrZ &lhs, double rhs);

public:
   XYZrZ(double x, double y, double z, double Rz);
   XYZrZ(double x, double y, double z)
      : XYZrZ(x, y, z, 0.0)
   {
   }
   XYZrZ(const CartVec &xyz);
   XYZrZ(const CartVec &xyz, double Rz);

   /// Compound assignment operator [[x,y,z], Rz] += [a,b,c] =>
   /// [[x+a,y+b,z+c], Rz]
   XYZrZ &operator+=(const CartVec &rhs)
   {
      position += rhs;
      return *this;
   }
   /// [[x,y,z], Rz] -= [a,b,c] => [[x-a,y-b,z-c], Rz]
   XYZrZ &operator-=(const CartVec &rhs)
   {
      position -= rhs;
      return *this;
   }

   CartVec heading() const
   {
      return {cos(math::toRadians(Rz)), sin(math::toRadians(Rz))};
   }

   CartVec atDistance(double d) const
   {
      return {position.get_x() + d * cos(math::toRadians(Rz)),
              position.get_y() + d * sin(math::toRadians(Rz)),
              position.get_z()};
   }

   void draw() const override;
   double length() const { return position.length(); }

   CartVec position;
   double Rz;
};

#endif // XYZRZ_H
