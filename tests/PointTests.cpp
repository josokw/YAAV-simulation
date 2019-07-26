#include "CartVec.h"
#include "Point.h"
#include "catch.hpp"

TEST_CASE("Point class")
{
   SECTION("Initialisation")
   {
      Point p;

      REQUIRE(p.get_x() == Approx(0.0));
      REQUIRE(p.get_y() == Approx(0.0));
      REQUIRE(p.get_z() == Approx(0.0));
   }

   SECTION("Operators")
   {
      Point p;

      p += CartVec{1, 1, 1};
      REQUIRE(p.get_x() == Approx(1.0));
      REQUIRE(p.get_y() == Approx(1.0));
      REQUIRE(p.get_z() == Approx(1.0));

      p -= CartVec::UNIT_Z;
      p -= CartVec::UNIT_Y;
      REQUIRE(p.get_x() == Approx(1.0));
      REQUIRE(p.get_y() == Approx(0.0));
      REQUIRE(p.get_z() == Approx(0.0));

      const Point p1{1.0, 1.0, 1.0};
      const Point p2{2.0, 2.0, 2.0};

      CartVec v{p1 - p2}; // v = p1 - p2  ==>  v + p2 == p1
      REQUIRE(v == CartVec{-1.0, -1.0, -1.0});
      REQUIRE_FALSE(v == CartVec{-1.0, 1.0, 1.0});
      REQUIRE(v != CartVec{-1.0, 1.0, 1.0});

      REQUIRE((p2 + v) == p1);
   }

   SECTION("Distance")
   {
      Point p1{1.0, 0.0, 3.0};
      Point p2{-1.0, 0.0, 3.0};

      REQUIRE(p1.distance(p1) == Approx(0.0));
      REQUIRE(p1.distance(p2) == Approx(2.0));
   }

   SECTION("Rotation")
   {
      Point p{1.0, 0.0, 0.0};

      p.rotateAroundZ(std::cos(M_PI), std::sin(M_PI));
      REQUIRE(p == Point{-1.0, 0.0, 0.0});
   }
}
