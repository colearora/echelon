#include "inc/catch.h"
#include "inc/gaussian.h"

TEST_CASE("3x4 with 2 pivots", "[gaussian]")
{
    la::Matrix A = la::Matrix::fromRows(
        {
            {1, 2, 3, 4},
            {4, 5, 6, 7},
            {6, 7, 8, 9}
        });
    la::Gaussian::eliminate(A);
    REQUIRE(la::round(A) == la::Matrix::fromRows(
        {
            {1, 0, -1, -2},
            {0, 1,  2,  3},
            {0, 0,  0,  0}
        }));
}