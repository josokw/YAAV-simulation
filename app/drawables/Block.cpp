#include "Block.h"

Block::Block(double l, double w, double h, const XYZrZ &xyzRz)
   : Drawable()
   , _l(l)
   , _h(h)
   , _w(w)
   , _XYZrZ(xyzRz)
   , _corners()
{
   _corners.addVertex(CartVec(_XYZrZ.position.get_x() - 0.5 * _l,
                              _XYZrZ.position.get_y() - 0.5 * _w, 0));
   _corners.addVertex(CartVec(_XYZrZ.position.get_x() + 0.5 * _l,
                              _XYZrZ.position.get_y() - 0.5 * _w, 0));
   _corners.addVertex(CartVec(_XYZrZ.position.get_x() + 0.5 * _l,
                              _XYZrZ.position.get_y() + 0.5 * _w, 0));
   _corners.addVertex(CartVec(_XYZrZ.position.get_x() - 0.5 * _l,
                              _XYZrZ.position.get_y() + 0.5 * _w, 0));
   _corners.calcNormal();
}

void Block::draw() const
{
   double lx = 0.5 * _l;
   double ly = 0.5 * _h;
   double lz = 0.5 * _w;

   glPushMatrix();
   glTranslatef(_XYZrZ.position.get_x(), _XYZrZ.position.get_y(),
                _XYZrZ.position.get_z());
   glRotatef(_XYZrZ.Rz, 0.0, 0.0, 1.0);

   glColor3f(1.0f, 0.5f, 0.0f);

   glBegin(GL_QUADS);
   glNormal3f(0, 1, 0);
   glVertex3f(+lx, +ly, -lz);
   glVertex3f(-lx, +ly, -lz);
   glVertex3f(-lx, +ly, +lz);
   glVertex3f(+lx, +ly, +lz);

   glNormal3f(0, -1, 0);
   glVertex3f(+lx, -ly, +lz);
   glVertex3f(-lx, -ly, +lz);
   glVertex3f(-lx, -ly, -lz);
   glVertex3f(+lx, -ly, -lz);

   glNormal3f(0, 0, 1);
   glVertex3f(+lx, -ly, +lz);
   glVertex3f(-lx, -ly, +lz);
   glVertex3f(-lx, +ly, +lz);
   glVertex3f(+lx, +ly, +lz);

   glNormal3f(-1, 0, 0);
   glVertex3f(-lx, +ly, +lz);
   glVertex3f(-lx, +ly, -lz);
   glVertex3f(-lx, -ly, -lz);
   glVertex3f(-lx, -ly, +lz);

   glNormal3f(1, 0, 0);
   glVertex3f(+lx, +ly, -lz);
   glVertex3f(+lx, +ly, +lz);
   glVertex3f(+lx, -ly, +lz);
   glVertex3f(+lx, -ly, -lz);

   glNormal3f(0, 0, -1);
   glColor3f(1.0f, 0.7f, 0.4f);
   glVertex3f(+lx, -ly, -lz);
   glVertex3f(-lx, -ly, -lz);
   glVertex3f(-lx, +ly, -lz);
   glVertex3f(+lx, +ly, -lz);
   glEnd();

   glPopMatrix();
}
