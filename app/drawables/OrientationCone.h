#ifndef ORIENTATIONCONE_H
#define ORIENTATIONCONE_H

#include "Drawable.h"
#include "XYZrZ.h"

class OrientationCone : public Drawable
{
   friend OrientationCone operator*(const OrientationCone &lhs, double rhs);
   friend OrientationCone operator*(double lhs, const OrientationCone &rhs);

public:
   static const OrientationCone OcX;
   static const OrientationCone OcY;
   static const OrientationCone OcZ;

   OrientationCone(double red, double green, double blue, const XYZrZ &xyzRz);
   OrientationCone(const OrientationCone &ocone);
   OrientationCone &operator=(const OrientationCone &) = delete;
   ~OrientationCone() override;

   void draw() const override;

private:
   double red_, green_, blue_;
   XYZrZ XYZrZ_;
   double size_;
   GLUquadricObj *pBody_;
};

#endif // ORIENTATIONCONE_H
