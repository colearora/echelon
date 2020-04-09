#include "inc/catch.h"
#include "inc/util.h"

#include <vector>
#include <iostream>

TEST_CASE("approxEqual", "[util]")
{
    std::vector<std::pair<float, bool>> tests =
        {
            {0.1, false},
            {0.01, false},
            {0.001, false},
            {0.0001, false},
            {0.00001, false},
            {0.000001, false},
            {0.0000001, true},
            {0.00000001, true},
            {0.00000000, true},
        };

    for (auto test : tests)
    {
        // std::cerr << test.first << " " << la::approxEqual(test.first, 0.0F) << std::endl;
        CHECK(la::approxEqual(test.first, 0.0F) == test.second);
    }
}