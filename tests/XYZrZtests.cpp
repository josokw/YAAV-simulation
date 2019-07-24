#include "XYZrZ.h"
#include "catch.hpp"

#include <sstream>

TEST_CASE("XYZrZ class")
{
   SECTION("Initialisation and functions")
   {
      XYZrZ xyzRz{{Point::ORIGIN}};

      auto [position, rZ] = xyzRz.getPositionRz();
      REQUIRE(position == Point{0.0, 0.0, 0.0});
      REQUIRE(rZ == Approx(0.0));
      REQUIRE(xyzRz.heading() == CartVec::UNIT_X);

      REQUIRE(xyzRz.atDistance(3.0) == Point{3.0, 0.0});

      xyzRz += 90.0;
      REQUIRE(xyzRz.getRz() == Approx(90.0));
      xyzRz -= 45.0;
      REQUIRE(xyzRz.getRz() == Approx(45.0));
   }
}
