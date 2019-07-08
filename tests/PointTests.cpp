#include "Point.h"
#include "CartVec.h"
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

      CartVec v{Point{1.0, 1.0, 1.0} - Point{2.0, 2.0, 2.0}};
      REQUIRE(v == CartVec{1.0, 1.0, 1.0});
   }
}