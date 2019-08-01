#include "Edge.h"
#include "Point.h"
#include "catch.hpp"

TEST_CASE("Edge class")
{
   SECTION("Get closest point")
   {
      const math::Point P1{0.0, 0.0};
      const math::Point P2{1.0, 0.0};
      math::Edge edge{P1, P2};

      math::Point p = edge.getClosestPoint({0.0, 0.0});
      REQUIRE(p == P1);

      p = edge.getClosestPoint({1.0, 1.0});
      REQUIRE(p == P2);

      p = edge.getClosestPoint({0.5, 1.0});
      REQUIRE(p == math::Point{0.5, 0.0});

      p = edge.getClosestPoint({-0.5, 1.0});
      REQUIRE(p == math::Point{P1});

      p = edge.getClosestPoint({-0.5, 1.0});
      REQUIRE(p == P1);
   }
}