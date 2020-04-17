#include "inc/catch.h"
#include "inc/vector.h"

TEST_CASE("vector: construction and access", "[vector]") {
    la::Vector u(3);
    for (int i = 0; i < u.size(); ++i) {
        u[i] = 1.0F;
    }
    la::Vector v(3, 1.0F);
    la::Vector w{1.0F, 1.0F, 1.0F};
    la::Vector x(w);
    la::Vector y = (0.5F * w) + (0.5F * x);
    REQUIRE(u == v);
    REQUIRE(v == w);
    REQUIRE(w == x);
    REQUIRE(x == y);
}

TEST_CASE("vector: linear combination", "[vector]") {
    float x1 = -4;
    float x2 =  3;
    la::Vector a1{1, 2, -1};
    la::Vector a2{2, 3,  6};
    la::Vector  b{2, 1, 22};
    REQUIRE(x1 * a1 + x2 * a2 == b);
}

TEST_CASE("vector: iteration", "[vector]") {
    la::Vector v(2, 1.0F);
    for (float entry : v) {
        REQUIRE(entry == 1.0F);
    }
    for (float& entry : v) {
        REQUIRE(entry == 1.0F);
    }
    for (const float& entry : v) {
        REQUIRE(entry == 1.0F);
    }
    for (int i = 0; i < v.size(); ++i) {
        REQUIRE(v[i] == 1.0F);
    }
}