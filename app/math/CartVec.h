#ifndef CARTVEC_H
#define CARTVEC_H

#include <cmath>
#include <iosfwd>
#include <tuple>

/// Represents a Cartesian vector [x,y,z] in 3D space.
/// \short 3D Cartesian vector.
class CartVec final
{
   /// Testing for equality.
   /// \see CartVec::eps
   friend bool operator==(const CartVec &lhs, const CartVec &rhs);
   friend bool operator!=(const CartVec &lhs, const CartVec &rhs);
   /// cv = cv1 + cv2
   friend CartVec operator+(const CartVec &lhs, const CartVec &rhs);
   /// cv = cv1 - cv2
   friend CartVec operator-(const CartVec &lhs, const CartVec &rhs);
   /// Scaling: cv1 = cv2 * scalar
   friend CartVec operator*(double lhs, const CartVec &rhs);
   /// Scaling: cv1 = scalar * cv2
   friend CartVec operator*(const CartVec &lhs, double rhs);
   /// Scaling: cv1 = cv2 / scalar
   friend CartVec operator/(const CartVec &lhs, double rhs);
   /// Output format: [x,y,z]
   friend std::ostream &operator<<(std::ostream &os, const CartVec &rhs);
   /// Input format: [x,y,z]  extra whitespaces are allowed.
   friend std::istream &operator>>(std::istream &is, CartVec &rhs);

public:
   static const CartVec ZERO;
   static const CartVec UNIT_X;
   static const CartVec UNIT_Y;
   static const CartVec UNIT_Z;

   static double eps;

   CartVec() = default;
   CartVec(double x, double y, double z = 0.0);

   double get_x() const { return x_; }
   double get_y() const { return y_; }
   double get_z() const { return z_; }
   std::tuple<double, double, double> get_xyz() const { return {x_, y_, z_}; }
   void set_x(double x) { x_ = x; }
   void set_y(double y) { y_ = y; }
   void set_z(double z) { z_ = z; }

   /// Unary + operator: +cv
   CartVec operator+() const { return *this; }
   /// Unary - operator: -cv
   CartVec operator-() const { return {-x_, -y_, -z_}; }
   /// Compound assignment operator: cv1 += cv2
   CartVec &operator+=(const CartVec &rhs)
   {
      x_ += rhs.x_;
      y_ += rhs.y_;
      z_ += rhs.z_;
      return *this;
   }
   /// Compound assignment operator: cv1 -= cv2
   CartVec &operator-=(const CartVec &rhs)
   {
      x_ -= rhs.x_;
      y_ -= rhs.y_;
      z_ -= rhs.z_;
      return *this;
   }
   /// Compound assignment operator: cv1 *= scalar
   CartVec &operator*=(double rhs)
   {
      x_ *= rhs;
      y_ *= rhs;
      z_ *= rhs;
      return *this;
   }
   /// Compound assignment operator: cv1 /= scalar
   CartVec &operator/=(double rhs)
   {
      x_ /= rhs;
      y_ /= rhs;
      z_ /= rhs;
      return *this;
   }

   /// Calculates length: ||vector||
   double length() const { return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_); }
   /// Distance to other end point of a CartVec.
   double distance(const CartVec &cv) const;
   /// Sets vector to unit length.
   void normalize() { *this /= length(); }
   /// Calculates inner product.
   double dot(const CartVec &v) const
   {
      return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
   }
   /// Calulates cross product.
   CartVec cross(const CartVec &cv) const
   {
      return {y_ * cv.z_ - z_ * cv.y_, -x_ * cv.z_ + z_ * cv.x_,
              x_ * cv.y_ - y_ * cv.x_};
   }
   /// Calculates the angle [rad] between vector and v.
   double angle(const CartVec &v) const;
   /// Rotates around z.
   void rotateAroundZ(double cosPhi, double sinPhi);
   /// Rotates around y.
   void rotateAroundY(double cosPhi, double sinPhi);
   /// Rotates around x.
   void rotateAroundX(double cosPhi, double sinPhi);
   /// Rotates around an arbitrarily rotation axis.
   void rotateAround(const CartVec &axis, double cosPhi, double sinPhi);

private:
   double x_{0.0};
   double y_{0.0};
   double z_{0.0};
};

#endif // CARTVEC_H
