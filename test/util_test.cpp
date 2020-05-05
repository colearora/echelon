#include "inc/catch.h"
#include "inc/util.h"

#include <vector>
#include <iostream>

TEST_CASE("util: approxEqual", "[util]")
{
    std::vector<std::pair<float, bool>> tests =
        {
            {0.1F, false},
            {0.01F, false},
            {0.001F, false},
            {0.0001F, false},
            {0.00001F, true},
            {0.000001F, true},
            {0.0000001F, true},
            {0.0F, true}
        };

    for (auto test : tests)
    {
        float f = test.first;
        bool b = test.second;
        // std::cerr << f << " " << la::approxEqual(f, 0) << std::endl;
        REQUIRE(la::approxEqual(f, 0) == b);
    }
}