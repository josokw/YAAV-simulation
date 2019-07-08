#include "CartVec.h"
#include "catch.hpp"

TEST_CASE("CartVec class")
{
   SECTION("Constants")
   {
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

   SECTION("Initialisation")
   {
      CartVec cv;

      REQUIRE(cv.get_x() == Approx(0.0));
      REQUIRE(cv.get_y() == Approx(0.0));
      REQUIRE(cv.get_z() == Approx(0.0));
   }

   SECTION("Operators")
   {
      CartVec cv1{1.0, 0.0, 0.5};
      CartVec cv2{1.0, 1.0, 0.5};
      CartVec cv3;

      cv3 = cv1 + cv2;
      REQUIRE(cv3.get_x() == Approx(2.0));
      REQUIRE(cv3.get_y() == Approx(1.0));
      REQUIRE(cv3.get_z() == Approx(1.0));

      cv3 = cv1 - cv2;
      REQUIRE(cv3.get_x() == Approx(0.0));
      REQUIRE(cv3.get_y() == Approx(-1.0));
      REQUIRE(cv3.get_z() == Approx(0.0));

      cv3 = 3 * cv1;
      REQUIRE(cv3.get_x() == Approx(3.0));
      REQUIRE(cv3.get_y() == Approx(0.0));
      REQUIRE(cv3.get_z() == Approx(1.5));

      cv3 = cv1 * 3;
      REQUIRE(cv3.get_x() == Approx(3.0));
      REQUIRE(cv3.get_y() == Approx(0.0));
      REQUIRE(cv3.get_z() == Approx(1.5));

      bool test1{cv1 == cv1};
      bool test2{cv1 == cv2};
      REQUIRE(test1);
      REQUIRE_FALSE(test2);

      test1 = cv1 != cv1;
      test2 = cv1 != cv2;
      REQUIRE_FALSE(test1);
      REQUIRE(test2);
   }

   SECTION("Dot product")
   {
      CartVec cv1{1.0, 1.0, 1.0};
      CartVec cv2{-1.0, 1.0, 0.0};

      REQUIRE(cv1.dot(cv2) == Approx(0.0));
   }

   SECTION("Cross product")
   {
      CartVec cv1{1.0, 0.0, 0.0};
      CartVec cv2{0.0, 1.0, 0.0};

      REQUIRE(cv1.cross(cv2) == CartVec{0, 0, 1});
   }

   SECTION("Length")
   {
      REQUIRE(CartVec::UNIT_X.length() == Approx(1.0));
      REQUIRE(CartVec::UNIT_Y.length() == Approx(1.0));
      REQUIRE(CartVec::UNIT_Z.length() == Approx(1.0));
      REQUIRE(CartVec::ZERO.length() == Approx(0.0));
   }

   SECTION("Input streams") { CartVec cv; }
}
