#include "CollisionDetector.h"
#include "Polygon.h"

#include "catch.hpp"

TEST_CASE("CollissionDtector class")
{
   SECTION("Collision detection circle and circle")
   {
      physics::CollisionDetector cd;

      bool col = cd.isColliding({{0, 0}, 1}, {{0, 0.5}, 1});
      REQUIRE(col);
      col = cd.isColliding({{0, 0}, 0.5}, {{0, 0.5}, 1});
      REQUIRE(col);
      col = cd.isColliding({{0, 0}, 0.5}, {{1.5, 0.5}, 1});
      REQUIRE_FALSE(col);
   }

   SECTION("Collision detection circle and polygon")
   {
      physics::CollisionDetector cd;
      const math::Polygon p1{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}};
      math::circle_t circle{{-0.4, 0.0}, 1.0};

      bool col;
      col = cd.isColliding({{0, 0.5}, 1}, p1);
      REQUIRE(col);
      col = cd.isColliding({{-0.4, 0}, 0.5}, p1);
      REQUIRE(col);
      col = cd.isColliding({{0, -0.6}, 0.5}, p1);
      REQUIRE_FALSE(col);
   }
}