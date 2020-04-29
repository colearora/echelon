#include "inc/catch.h"
#include "inc/bag.h"
#include "inc/vector.h"

TEST_CASE("bag: of vectors", "[bag]")
{
    la::Vector e1{1, 0, 0};
    la::Vector e2{0, 1, 0};
    la::Vector e3{0, 0, 1};
    la::Bag<la::Vector> bag;
    bag.add(e1);
    bag.add(e2);
    bag.add(e3);
    for (int i = 0; i < 3; ++i)
    {
        bag.add(new la::Vector{1, 1, 1});
    }
    REQUIRE(bag.size() == 6);
    for (int i = 0; i < bag.size(); ++i)
    {
        switch (i)
        {
        case 0:
            REQUIRE(bag[i] == e1);
            break;
        case 1:
            REQUIRE(bag[i] == e2);
            break;
        case 2:
            REQUIRE(bag[i] == e3);
            break;
        case 3:
        case 4:
        case 5:
            REQUIRE(bag[i] == la::Vector{1, 1, 1});
            break;
        default:
            REQUIRE(false);
            break;
        }
    }
}