#include "Polygon.h"
#include "Edge.h"
#include "MathDef.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

namespace math {

std::ostream &operator<<(std::ostream &os, const math::Polygon &rhs)
{
   os << "Poly[";
   for (const auto &point : rhs.getVertices()) {
      os << ' ' << point;
   }
   os << " Normal" << rhs.getNormal() << "]";
   return os;
}

} // namespace math

math::Polygon::Polygon(const std::initializer_list<Point> &cvlist)
   : vertices_{cvlist}
   , normal_{}
{
   // for (auto i = begin(cvlist); i != end(cvlist); ++i) {
   //    vertices_.push_back(*i);
   // }
   calcNormal();
}

math::Polygon::Polygon(const std::vector<Point> &vertices)
   : vertices_{vertices}
   , normal_{}
{
   calcNormal();
}

void math::Polygon::addVertex(const Point &vertex)
{
   vertices_.push_back(vertex);
}

void math::Polygon::calcNormal()
{
   CartVec temp1 = vertices_[2] - vertices_[1];
   CartVec temp2 = vertices_[0] - vertices_[1];
   normal_ = temp1.cross(temp2);
   normal_.normalize();
}

bool math::Polygon::isFacing(const Point &point) const
{
   CartVec temp = point - vertices_[0];

   return normal_.dot(temp) >= 0.0;
}

math::Edge math::Polygon::getEdge(std::size_t index) const
{
   auto size{vertices_.size()};

   return math::Edge{vertices_[index % size], vertices_[(index + 1) % size]};
}

Point math::Polygon::getClosestPointToEdge(std::size_t index,
                                           const Point &p) const
{
   auto edge{getEdge(index)};
   CartVec v{edge.getEnd() - edge.getStart()};
   CartVec w{p - vertices_[index]};
   double wDotv{w.dot(v)};
   double t{wDotv / v.dot(v)};

   if (t < 0)
      t = 0;
   if (t > 1)
      t = 1;

   return vertices_[index] + v * t;
}

math::Polygon::minmaxXYZ_t math::Polygon::getMinMaxXYZ() const
{
   math::Polygon::minmaxXYZ_t result;
   result.maxX = vertices_[0].get_x();
   result.minX = vertices_[0].get_x();
   result.maxY = vertices_[0].get_y();
   result.minY = vertices_[0].get_y();
   result.maxZ = vertices_[0].get_z();
   result.minZ = vertices_[0].get_z();

   auto it = vertices_.begin();
   while (it != vertices_.end()) {
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
   for (auto &v : vertices_) {
      v += rhs;
   }
   return *this;
}

math::Polygon &math::Polygon::operator-=(const CartVec &rhs)
{
   for (auto &v : vertices_) {
      v -= rhs;
   }
   return *this;
}

void math::Polygon::rotateAroundX(double angle)
{
   double angleRadians{toRadians(angle)};
   double cosPhi{std::cos(angleRadians)};
   double sinPhi{std::sin(angleRadians)};

   for (auto &v : vertices_) {
      v.rotateAroundX(cosPhi, sinPhi);
   }
   calcNormal();
}

void math::Polygon::rotateAroundY(double angle)
{
   double angleRadians{toRadians(angle)};
   double cosPhi{std::cos(angleRadians)};
   double sinPhi{std::sin(angleRadians)};

   for (auto &v : vertices_) {
      v.rotateAroundY(cosPhi, sinPhi);
   }
   calcNormal();
}

void math::Polygon::rotateAroundZ(double angle)
{
   double angleRadians{toRadians(angle)};
   double cosPhi{std::cos(angleRadians)};
   double sinPhi{std::sin(angleRadians)};

   for (auto &v : vertices_) {
      v.rotateAroundZ(cosPhi, sinPhi);
   }
   calcNormal();
}

// void math::Polygon::rotateAroundXYZ(const CartVec &xyz, double angle)
// {
//    double angleRadians{toRadians(angle)};
//    double cosPhi{std::cos(angleRadians)};
//    double sinPhi{std::sin(angleRadians)};

//    for (auto &v : vertices_) {
//       v.rotateAround(xyz, cosPhi, sinPhi);
//    }
//    calcNormal();
// }

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
bool math::Polygon::isInside(const Point &point) const
{
   bool isIn{false};

   for (size_t i = 0, j = vertices_.size() - 1; i < vertices_.size(); j = i++) {
      if ((vertices_[i].get_y() > point.get_y()) !=
             (vertices_[j].get_y() > point.get_y()) and
          (point.get_x() < (vertices_[j].get_x() - vertices_[i].get_x()) *
                                 (point.get_y() - vertices_[i].get_y()) /
                                 (vertices_[j].get_y() - vertices_[i].get_y()) +
                              vertices_[i].get_x())) {
         isIn = !isIn;
      }
   }

   return isIn;
}
