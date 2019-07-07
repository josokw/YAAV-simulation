#ifndef BALL_H
#define BALL_H

#include "Drawable.h"
#include "math/XYZrZ.h"

class Ball : public Drawable
{
public:
   Ball(double R, const XYZrZ &xyzRz);
   Ball(const Ball &) = delete;
   Ball &operator=(const Ball &) = delete;
   virtual ~Ball() = default;
   virtual void draw() const;

private:
   double m_R;
   XYZrZ m_XYZrZ;
   GLUquadricObj *m_pBody;
};

#endif // BALL_H
