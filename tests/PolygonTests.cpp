#include "Point.h"
#include "Polygon.h"
#include "catch.hpp"

TEST_CASE("Polygon class")
{
   SECTION("Is inside")
   {
      math::Polygon p1{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}};

      REQUIRE(p1.isInside({0.5, 0.25}));
      REQUIRE_FALSE(p1.isInside({-0.5, 0.25}));

      math::Polygon p2{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.5, 0.5}};

      REQUIRE(p2.isInside({0.25, 0.25}));
      REQUIRE_FALSE(p2.isInside({-0.25, -0.25}));
   }

   SECTION("Normal")
   {
      math::Polygon p1{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}};

      REQUIRE(p1.getNormal() == CartVec::UNIT_Z);

      math::Polygon p2{{0.1, 0.0}, {1.1, 0.0}, {1.0, 1.0}, {0.5, 0.6}};

      REQUIRE(p2.getNormal() == CartVec::UNIT_Z);
   }
}
