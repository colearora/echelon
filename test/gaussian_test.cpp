#include "inc/catch.h"
#include "inc/gaussian.h"

TEST_CASE("gaussian: 3x4 with 2 pivots", "[gaussian]")
{
    la::Matrix A = la::Matrix::fromRows(
        {
            {1, 2, 3, 4},
            {4, 5, 6, 7},
            {6, 7, 8, 9}
        });
    la::Matrix U = la::Matrix::fromRows(
        {
            {1, 0, -1, -2},
            {0, 1,  2,  3},
            {0, 0,  0,  0}
        });
    la::eliminate(A);
    REQUIRE(la::approxEqual(A, U));
}

TEST_CASE("gaussian: 3x4 with 3 pivots", "[gaussian]")
{
    la::Matrix A = la::Matrix::fromRows(
        {
            {36, 51,  13, 33},
            {52, 34,  74, 45},
            { 0,  7, 1.1,  3}
        });
    la::Matrix U = la::Matrix::fromRows(
        {
            {1, 0, 0, 0.277},
            {0, 1, 0, 0.392},
            {0, 0, 1, 0.233}
        });
    la::eliminate(A);
    REQUIRE(la::approxEqual(A, U, 1e-3F));
}

TEST_CASE("gaussian: 4x5 with 4 pivots", "[gaussian]")
{
    la::Matrix A = la::Matrix::fromRows(
        {
            {12, -7,  0, -4,  40},
            {-7, 15, -6,  0,  30},
            { 0, -6, 14, -5,  20},
            {-4,  0, -5, 13, -10}
        });
    la::Matrix U = la::Matrix::fromRows(
        {
            {1, 0, 0, 0, 11.43},
            {0, 1, 0, 0, 10.55},
            {0, 0, 1, 0,  8.04},
            {0, 0, 0, 1,  5.84}
        });
    la::eliminate(A);
    REQUIRE(la::approxEqual(A, U, 1e-3F));
}