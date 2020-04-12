#include "inc/catch.h"
#include "inc/rational.h"

TEST_CASE("rational: construction and operations", "[rational]") {
    REQUIRE(la::Rational(0, 1) == la::Rational(0, 3));
    REQUIRE(la::Rational(7, -1) == la::Rational(-7, 1));
    REQUIRE(la::Rational(7, 1) == -1 * la::Rational(7, -1));
    REQUIRE(la::Rational(7, 2) == la::Rational(21, 6));
    REQUIRE(la::Rational(7, 2) + la::Rational(8, 3) == la::Rational(37, 6));
    REQUIRE(la::Rational(7, 2) * la::Rational(8, 3) == la::Rational(28, 3));
    REQUIRE(la::Rational(7, 2) - la::Rational(7, 2) == 0);
}
