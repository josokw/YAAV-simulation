#include "CartVec.h"
#include "Circle.h"
#include "catch.hpp"

TEST_CASE("Circle class")
{
   SECTION("Initialisation")
   {
      Circle c;

      auto [center, r] = c.getCenterRadius();

      REQUIRE(center == Point::ORIGIN);
      REQUIRE(r == Approx(1.0));
   }

   SECTION("Operators")
   {
      Circle c1;
      Point p{1.0, 1.0};
      Circle c2{p};

      c1 += CartVec{1.0, 1.0};
      REQUIRE(c1 == c2);

      Circle c3{Point::ORIGIN, 10};
      Circle c4;

      c4 = c3 + CartVec{2.0, 3.0};
      REQUIRE(c4 == Circle{Point{2.0, 3.0}, 10});
      c4 -= 2 * CartVec{2.0, 3.0};
      REQUIRE(c4 ==  Circle{Point{-2.0, -3.0}, 10});
   }
}
