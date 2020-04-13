#include "inc/catch.h"
#include "inc/vector.h"

TEST_CASE("vector: construction and access", "[vector]") {
    la::Vector u(3);
    for (std::size_t i = 0; i < u.dim(); ++i) {
        u[i] = 1.0F;
    }
    la::Vector v(3, 1.0F);
    la::Vector w{1.0F, 1.0F, 1.0F};
    la::Vector x(w);

    REQUIRE(u == v);
    REQUIRE(v == w);
    REQUIRE(w == x);
}