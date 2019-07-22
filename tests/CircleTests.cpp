#include "Circle.h"
#include "CartVec.h"
#include "catch.hpp"

TEST_CASE("Circle class")
{
   SECTION("Initialisation")
   {
      Circle c;

      auto [p, r] = c.get();

      REQUIRE(p == Point{0.0, 0.0, 0.0});
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
