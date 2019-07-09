#include "Block.h"

Block::Block(double length, double width, double height, const XYZrZ &xyzRz)
   : Drawable{}
   , length_{length}
   , height_{height}
   , width_{width}
   , XYZrZ_{xyzRz}
   , corners_{{XYZrZ_.position.get_x() - 0.5 * length_,
               XYZrZ_.position.get_y() - 0.5 * width_},
              {XYZrZ_.position.get_x() + 0.5 * length_,
               XYZrZ_.position.get_y() - 0.5 * width_},
              {XYZrZ_.position.get_x() + 0.5 * length_,
               XYZrZ_.position.get_y() + 0.5 * width_},
              {XYZrZ_.position.get_x() - 0.5 * length_,
               XYZrZ_.position.get_y() + 0.5 * width_}}
{
   corners_.calcNormal();
}

void Block::draw() const
{
   double lx = 0.5 * length_;
   double ly = 0.5 * height_;
   double lz = 0.5 * width_;

   glPushMatrix();
   glTranslatef(XYZrZ_.position.get_x(), XYZrZ_.position.get_y(),
                XYZrZ_.position.get_z());
   glRotatef(XYZrZ_.Rz, 0.0, 0.0, 1.0);

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
