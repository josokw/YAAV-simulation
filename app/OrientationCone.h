#ifndef ORIENTATIONCONE_H
#define ORIENTATIONCONE_H

#include "Drawable.h"
#include "math/XYZrZ.h"

class OrientationCone : public Drawable
{
   friend OrientationCone operator*(const OrientationCone &lhs,
                                    double rhs);
   friend OrientationCone operator*(double lhs,
                                    const OrientationCone &rhs);

public:
   static const OrientationCone OcX;
   static const OrientationCone OcY;
   static const OrientationCone OcZ;

   OrientationCone(double r, double g, double b, const XYZrZ &xyzRz);
   OrientationCone(const OrientationCone &ocone);
   OrientationCone &operator=(const OrientationCone &) = delete;
   virtual ~OrientationCone();
   virtual void draw() const;

private:
   double m_r, m_g, m_b;
   XYZrZ m_XYZrZ;
   double m_size;
   GLUquadricObj *m_pBody;
};

#endif // ORIENTATIONCONE_H
