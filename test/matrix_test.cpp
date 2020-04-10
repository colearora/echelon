#include "inc/catch.h"
#include "inc/matrix.h"

TEST_CASE("construction", "[matrix]")
{
    la::Matrix A(4, 4, 0.0F);
    for (int i = 0; i < 4; ++i)
    {
        A(i, 1) = i;
    }
    la::Matrix B = la::Matrix::fromRows(
        {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 2, 0, 0},
            {0, 3, 0, 0},
        });
    la::Matrix C = la::Matrix::fromCols(
        {
            {0, 0, 0, 0},
            {0, 1, 2, 3},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        });
    la::Matrix D(C);

    REQUIRE(A == B);
    REQUIRE(B == C);
    REQUIRE(C == D);
}

TEST_CASE("size", "[matrix]")
{
    la::Matrix A(6, 4);
    la::Matrix B(A);
    la::Matrix C(4, 6);
    la::Matrix D(4, 4);
    la::Matrix v(6, 1);
    la::Matrix w(1, 6);

    REQUIRE(A.rows() == 6);
    REQUIRE(A.cols() == 4);
    REQUIRE(A.size() == std::pair<int, int>{6, 4});
    REQUIRE(A.size() == B.size());
    REQUIRE(A.size() != C.size());
    REQUIRE(!A.isSquare());
    REQUIRE(D.isSquare());
    REQUIRE(!D.isVector());
    REQUIRE(v.isVector());
    REQUIRE(w.isVector());
}

TEST_CASE("row operations", "[matrix]")
{
    la::Matrix A = la::Matrix::fromRows(
        {
            {2, 2, 2},
            {1, 1, 1},
            {3, 3, 3}
        });

    SECTION("scale")
    {
        A.scaleRow(0, 1.0F / 2);
        REQUIRE(A == la::Matrix::fromRows(
            {
                {1, 1, 1},
                {1, 1, 1},
                {3, 3, 3}
            }));
    }
    SECTION("swap")
    {
        A.swapRows(0, 1);
        REQUIRE(A == la::Matrix::fromRows(
            {
                {1, 1, 1},
                {2, 2, 2},
                {3, 3, 3}
            }));
    }
    SECTION("replace")
    {
        A.replaceRow(2, 0, -3.0F / 2);
        REQUIRE(A == la::Matrix::fromRows(
            {
                {2, 2, 2},
                {1, 1, 1},
                {0, 0, 0}
            }));
    }
}

TEST_CASE("transpose", "[matrix]")
{
    la::Matrix A(2, 4);
    la::Matrix B = la::transpose(A);

    REQUIRE(A.rows() == B.cols());
    REQUIRE(A.cols() == B.rows());
    for (int i = 0; i < A.rows(); ++i) 
    {
        for (int j = 0; j < A.cols(); ++j) 
        {
            REQUIRE(A(i, j) == B(j, i));
        }
    }
}