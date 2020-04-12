#include "inc/catch.h"
#include "inc/util.h"

#include <vector>
#include <iostream>

TEST_CASE("util: approxEqual", "[util]") {
    std::vector<std::pair<float, bool>> tests = {
        {0.1F, false},
        {0.01F, false},
        {0.001F, false},
        {0.0001F, false},
        {0.00001F, false},
        {0.000001F, false},
        {0.0000001F, true},
        {0.00000001F, true},
        {0.0F, true}};

    for (auto test : tests) {
        // std::cerr << test.first << " " << la::approxEqual(test.first, 0.0F) << std::endl;
        REQUIRE(la::approxEqual(test.first, 0.0F) == test.second);
    }
}