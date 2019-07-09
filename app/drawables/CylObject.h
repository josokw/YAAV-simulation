#ifndef CYLOBJECT_H
#define CYLOBJECT_H

#include "Drawable.h"
#include "math/MathDef.h"
#include "math/XYZrZ.h"
#include <iosfwd>

/// Cylindrical shaped opject (e.g. chair and table legs).
class CylObject : public Drawable
{
   /// Input format: R H x y z Rz
   friend std::istream &operator>>(std::istream &is, CylObject &rhs);

public:
   CylObject(double R, double H, const XYZrZ &xyzRz);
   CylObject(const CylObject &cylobj);
   CylObject &operator=(const CylObject &cylobj);
   virtual ~CylObject() override;
   virtual void draw() const override;

   math::circle_t getCollisionShape() const
   {
      return math::circle_t(_XYZrZ.position, _R);
   }
   // private:
   double _R;
   double _H;
   XYZrZ _XYZrZ;
   GLUquadricObj *_pBody;
};

#endif // CYLOBJECT_H
