#include "Polygon.h"
#include "MathDef.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

// math::Polygon p = { { 1, 2, 3 }, { 2, 3, 4 }, { 5, 7, 8 } };

namespace math {

std::ostream &operator<<(std::ostream &out, const math::Polygon &rhs)
{
   std::copy(rhs.getVertices().begin(), rhs.getVertices().end(),
             std::ostream_iterator<CartVec>(out, " "));
   out << "N = " << rhs.getNormal();
   return out;
}
} // namespace math

math::Polygon::Polygon()
   : _vertices()
   , _normal()
{
}

math::Polygon::Polygon(const std::initializer_list<CartVec> &cvlist)
   : _vertices()
   , _normal()
{
   for (auto i = begin(cvlist); i != end(cvlist); ++i) {
      _vertices.push_back(*i);
   }
   calcNormal();
}

math::Polygon::Polygon(const std::vector<CartVec> &vertices)
   : _vertices(vertices)
   , _normal()
{
   calcNormal();
}

void math::Polygon::addVertex(const CartVec &vertex)
{
   _vertices.push_back(vertex);
}

void math::Polygon::calcNormal()
{
   CartVec temp1(_vertices[2]);
   CartVec temp2(_vertices[0]);
   temp1 -= _vertices[1];
   temp2 -= _vertices[1];
   _normal = temp1.cross(temp2);
   _normal.normalize();
}

bool math::Polygon::isFacing(const CartVec &point) const
{
   CartVec temp(point);
   temp -= _vertices[0];
   return _normal.dot(temp) >= 0.0f;
}

math::edge_t math::Polygon::getEdge(std::size_t index) const
{
   size_t size = _vertices.size();
   math::edge_t result = {_vertices[index % size],
                          _vertices[(index + 1) % size]};
   return result;
}

CartVec math::Polygon::getClosestPointToEdge(std::size_t index,
                                             const CartVec &p) const
{
   math::edge_t edge = getEdge(index);
   CartVec v(edge.end - edge.start);
   CartVec w(p - _vertices[index]);
   double wDotv = w.dot(v);
   double t = wDotv / v.dot(v);
   if (t < 0)
      t = 0;
   if (t > 1)
      t = 1;
   return _vertices[index] + v * t;
}

math::minmaxXYZ_t math::Polygon::getMinMaxXYZ() const
{
   math::minmaxXYZ_t result;
   result.maxX = _vertices[0].get_x();
   result.minX = _vertices[0].get_x();
   result.maxY = _vertices[0].get_y();
   result.minY = _vertices[0].get_y();
   result.maxZ = _vertices[0].get_z();
   result.minZ = _vertices[0].get_z();

   auto it = _vertices.begin();
   while (it != _vertices.end()) {
      result.maxX = std::max(result.maxX, it->get_x());
      result.maxY = std::max(result.maxY, it->get_y());
      result.maxZ = std::max(result.maxZ, it->get_z());
      result.minX = std::min(result.minX, it->get_x());
      result.minY = std::min(result.minY, it->get_y());
      result.minZ = std::max(result.minZ, it->get_z());
      ++it;
   }
   return result;
}

math::Polygon &math::Polygon::operator+=(const CartVec &rhs)
{
   for (auto &v : _vertices) {
      v += rhs;
   }
   return *this;
}

math::Polygon &math::Polygon::operator-=(const CartVec &rhs)
{
   for (auto &v : _vertices) {
      v -= rhs;
   }
   return *this;
}

void math::Polygon::rotateAroundX(double angle)
{
   double angleRadians = toRadians(angle);
   double cosPhi = std::cos(angleRadians);
   double sinPhi = std::sin(angleRadians);

   for (auto &v : _vertices) {
      v.rotateAroundX(cosPhi, sinPhi);
   }
   calcNormal();
}

void math::Polygon::rotateAroundY(double angle)
{
   double angleRadians = toRadians(angle);
   double cosPhi = std::cos(angleRadians);
   double sinPhi = std::sin(angleRadians);

   for (auto &v : _vertices) {
      v.rotateAroundY(cosPhi, sinPhi);
   }
   calcNormal();
}

void math::Polygon::rotateAroundZ(double angle)
{
   double angleRadians = toRadians(angle);
   double cosPhi = std::cos(angleRadians);
   double sinPhi = std::sin(angleRadians);

   for (auto &v : _vertices) {
      v.rotateAroundZ(cosPhi, sinPhi);
   }
   calcNormal();
}

void math::Polygon::rotateAroundXYZ(const CartVec &xyz, double angle)
{
   double angleRadians = toRadians(angle);
   double cosPhi = std::cos(angleRadians);
   double sinPhi = std::sin(angleRadians);

   for (auto &v : _vertices) {
      v.rotateAround(xyz, cosPhi, sinPhi);
   }
   calcNormal();
}

// int pnpoly(int nvert, float *vertx, float *verty, float testx, float
// testy)
//{
//  int i, j, c = 0;
//  for (i = 0, j = nvert-1; i < nvert; j = i++) {
//    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
//     (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) /
//     (verty[j]-verty[i]) + vertx[i]) )
//       c = !c;
//  }
//  return c;
//}
bool math::Polygon::isInside(const CartVec &point) const
{
   bool isIn = false;
   for (size_t i = 0, j = _vertices.size() - 1; i < _vertices.size(); j = i++) {
      if ((_vertices[i].get_y() > point.get_y()) !=
             (_vertices[j].get_y() > point.get_y()) &&
          (point.get_x() < (_vertices[j].get_x() - _vertices[i].get_x()) *
                                 (point.get_y() - _vertices[i].get_y()) /
                                 (_vertices[j].get_y() - _vertices[i].get_y()) +
                              _vertices[i].get_x())) {
         isIn = !isIn;
      }
   }
   return isIn;
}
