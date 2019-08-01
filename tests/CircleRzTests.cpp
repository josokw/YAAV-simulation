#include "CartVec.h"
#include "CircleRz.h"
#include "catch.hpp"

TEST_CASE("CircleRz class")
{
   SECTION("Initialisation")
   {
      math::CircleRz c1;

      auto [center, r, Rz] = c1.getCenterRadiusRz();

      REQUIRE(center == math::Point::ORIGIN);
      REQUIRE(r == Approx(1.0));
      REQUIRE(Rz == Approx(0.0));

      REQUIRE(c1.heading() == math::CartVec{1.0, 0.0});
   }

   SECTION("Operators")
   {
      math::CircleRz c1;
      math::Point p{1.0, 1.0};
      math::CircleRz c2{p};

      c1 += math::CartVec{1.0, 1.0};
      REQUIRE(c1 == c2);

      math::CircleRz c3{math::Point::ORIGIN, 10, 20};
      math::CircleRz c4;

      // c4 = c3 + math::CartVec{2.0, 3.0};
      // REQUIRE(c4 == math::CircleRz{math::Point{2.0, 3.0}, 10, 0.0});
      // c4 -= 2 * math::CartVec{2.0, 3.0};
      // REQUIRE(c4 == math::CircleRz{math::Point{-2.0, -3.0}, 10, 0.0});
   }
}