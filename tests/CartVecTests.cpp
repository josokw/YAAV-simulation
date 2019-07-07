#include "catch.hpp"
#include "CartVec.h"

TEST_CASE("CartVec class constants") {

   REQUIRE(CartVec::ZERO.get_x() == Approx(0.0));
   REQUIRE(CartVec::ZERO.get_y() == Approx(0.0));
   REQUIRE(CartVec::ZERO.get_z() == Approx(0.0));

   REQUIRE(CartVec::UNIT_X.get_x() == Approx(1.0));
   REQUIRE(CartVec::UNIT_X.get_y() == Approx(0.0));
   REQUIRE(CartVec::UNIT_X.get_z() == Approx(0.0));

   REQUIRE(CartVec::UNIT_Y.get_x() == Approx(0.0));
   REQUIRE(CartVec::UNIT_Y.get_y() == Approx(1.0));
   REQUIRE(CartVec::UNIT_Y.get_z() == Approx(0.0));

   REQUIRE(CartVec::UNIT_Z.get_x() == Approx(0.0));
   REQUIRE(CartVec::UNIT_Z.get_y() == Approx(0.0));
   REQUIRE(CartVec::UNIT_Z.get_z() == Approx(1.0));
}
