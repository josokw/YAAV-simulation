#include "CartVec.h"
#include "Circle.h"
#include "catch.hpp"

TEST_CASE("Circle class")
{
   SECTION("Initialisation")
   {
      Circle c;

      auto [center, r] = c.get_cr();

      REQUIRE(center == Point::ORIGIN);
      REQUIRE(r == Approx(1.0));
   }

   SECTION("Operators")
   {
      Circle c1;
      Point p{1.0, 1.0, 1.0};
      Circle c2{p};

      c1 += CartVec{1.0, 1.0, 1.0};
      REQUIRE(c1 == c2);
   }
}
