#include "CartVec.h"
#include "Circle.h"
#include "catch.hpp"

TEST_CASE("Circle class")
{
   SECTION("Initialisation")
   {
      math::Circle c1;

      auto [center, r] = c1.getCenterRadius();

      REQUIRE(center == Point::ORIGIN);
      REQUIRE(r == Approx(1.0));

      REQUIRE(math::Circle::INVALID == math::Circle{{0.0, 0.0, 0.0}, -1.0});

      math::Circle c2{Point{-1.0, 0, 0}, Point{1.0, 0.0}};
      REQUIRE(c2 == math::Circle{{0.0, 0.0}, 1.0});
      math::Circle c3{Point{-1.0, 1, 0}, Point{1.0, 1.0}};
      REQUIRE(c3 == math::Circle{{0.0, 1.0}, 1.0});

      math::Circle c4{Point{2.0, 1, 0}, Point{0.0, 5.0}, Point{-1.0, 2.0}};
      REQUIRE(c4 == math::Circle{{1.0, 3.0}, std::sqrt(5.0)});
   }

   SECTION("Operators")
   {
      math::Circle c1;
      Point p{1.0, 1.0};
      math::Circle c2{p};

      c1 += math::CartVec{1.0, 1.0};
      REQUIRE(c1 == c2);

      math::Circle c3{Point::ORIGIN, 10};
      math::Circle c4;

      c4 = c3 + math::CartVec{2.0, 3.0};
      REQUIRE(c4 == math::Circle{Point{2.0, 3.0}, 10});
      c4 -= 2 * math::CartVec{2.0, 3.0};
      REQUIRE(c4 == math::Circle{Point{-2.0, -3.0}, 10});
   }
}
