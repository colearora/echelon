#include "inc/catch.h"
#include "inc/vector.h"
#include "inc/rational.h"

TEST_CASE("vector: construction and access", "[vector]") {
    la::Vector<float, 3> u;
    for (std::size_t i = 0; i < u.dim(); ++i) {
        u[i] = 3.0F;
    }
    la::Vector<float, 3> v(3.0F);
    REQUIRE(u == v);
    
    la::Vector<la::Rational, 5> w;
    w[3] += la::Rational(1, 2);
    w[4] += la::Rational(1, 2);
    REQUIRE(w[3] + w[4] == 1);
}