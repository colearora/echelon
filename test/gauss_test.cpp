#include "inc/catch.h"
#include "inc/gauss.h"
#include <iostream>

TEST_CASE("gauss: 3x4 elimination with 2 pivots", "[gauss]")
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
    la::eliminate(A, la::partialPivotSelector);
    // std::cerr << A            << std::endl;
    // std::cerr << la::round(A) << std::endl;
    // std::cerr << U            << std::endl;
    REQUIRE(la::approxEqual(A, U));
}

TEST_CASE("gauss: 3x4 elimination with 3 pivots", "[gauss]")
{
    la::Matrix A = la::Matrix::fromRows(
        {
            {36, 51,  13, 33},
            {52, 34,  74, 45},
            { 0,  7, 1.1,  3}
        });
    la::Matrix U = la::Matrix::fromRows(
        {
            {1, 0, 0, 0.277223},
            {0, 1, 0, 0.391921},
            {0, 0, 1, 0.233231}
        });
    la::eliminate(A, la::partialPivotSelector);
    // std::cerr << A << '\n' << la::round(A) << std::endl;
    REQUIRE(la::approxEqual(A, U));
}

TEST_CASE("gauss: 4x5 elimination with 4 pivots", "[gauss]")
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
            {1, 0, 0, 0, 11.4342},
            {0, 1, 0, 0, 10.5502},
            {0, 0, 1, 0, 8.03566},
            {0, 0, 0, 1, 5.83961}
        });
    la::eliminate(A, la::partialPivotSelector);
    // std::cerr << A << '\n' << la::round(A) << std::endl;
    REQUIRE(la::approxEqual(A, U));
}

TEST_CASE("gauss: 4x4 LU factorization without interchanges", "[gauss]")
{
    la::Matrix A = la::Matrix::fromRows(
        {
            { 3, -7, -2,  2},
            {-3,  5,  1,  0},
            { 6, -4,  0, -5},
            {-9,  5, -5, 12}
        });
    la::Matrix L(A.rows(), A.rows());
    la::Matrix U(A.rows(), A.cols());
    la::factor(A, la::firstNonzeroPivotSelector, L, U);
    // std::cerr << "A\n"  << la::round(A)     << std::endl;
    // std::cerr << "L\n"  << la::round(L)     << std::endl;
    // std::cerr << "U\n"  << la::round(U)     << std::endl;
    // std::cerr << "LU\n" << la::round(L * U) << std::endl;
    REQUIRE(approxEqual(L, la::Matrix::fromRows(
        {
            { 1,  0, 0, 0},
            {-1,  1, 0, 0},
            { 2, -5, 1, 0},
            {-3,  8, 3, 1}
        })));
    REQUIRE(approxEqual(U, la::Matrix::fromRows(
        {
            {3, -7, -2,  2},
            {0, -2, -1,  2},
            {0,  0, -1,  1},
            {0,  0,  0, -1}
        })));
    REQUIRE(approxEqual(A, L * U));
}

TEST_CASE("gauss: 4x5 LU factorization with interchanges", "[gauss]")
{
    la::Matrix A = la::Matrix::fromRows(
        {
            { 1, -1,  5, -8, -7},
            {-2, -1, -4,  9,  1},
            { 4,  8, -4,  0, -8},
            { 2,  3,  0, -5,  3}
        });
    la::Matrix L(A.rows(), A.rows());
    la::Matrix U(A.rows(), A.cols());
    la::factor(A, la::partialPivotSelector, L, U);
    // std::cerr << "A\n"  << la::round(A)     << std::endl;
    // std::cerr << "L\n"  << la::round(L)     << std::endl;
    // std::cerr << "U\n"  << la::round(U)     << std::endl;
    // std::cerr << "LU\n" << la::round(L * U) << std::endl;
    REQUIRE(approxEqual(A, L * U));
}

TEST_CASE("gauss: 5x4 LU factorization with interchanges", "[gauss]")
{
    la::Matrix A = la::Matrix::fromRows(
        {
            { 2, -4, -2,  3},
            { 6, -9, -5,  8},
            { 2, -7, -3,  9},
            { 4, -2, -2, -1},
            {-6,  3,  3,  4}
        });
    la::Matrix L(A.rows(), A.rows());
    la::Matrix U(A.rows(), A.cols());
    la::factor(A, la::partialPivotSelector, L, U);
    // std::cerr << "A\n"  << la::round(A)     << std::endl;
    // std::cerr << "L\n"  << la::round(L)     << std::endl;
    // std::cerr << "U\n"  << la::round(U)     << std::endl;
    // std::cerr << "LU\n" << la::round(L * U) << std::endl;
    REQUIRE(approxEqual(A, L * U));
}

TEST_CASE("gauss: 8x8 LU factorization without interchanges", "[gauss]")
{
    la::Matrix A = la::Matrix::fromRows(
        {
            { 4, -1, -1,  0,  0,  0,  0,  0},
            {-1,  4,  0,  1,  0,  0,  0,  0},
            {-1,  0,  4, -1, -1,  0,  0,  0},
            { 0, -1, -1,  4,  0, -1,  0,  0},
            { 0,  0, -1,  0,  4, -1, -1,  0},
            { 0,  0,  0, -1, -1,  4,  0, -1},
            { 0,  0,  0,  0, -1,  0,  4, -1},
            { 0,  0,  0,  0,  0, -1, -1,  4}
        });
    la::Matrix L(A.rows(), A.rows());
    la::Matrix U(A.rows(), A.cols());
    la::factor(A, la::firstNonzeroPivotSelector, L, U);
    // std::cerr << "A\n"  << la::round(A)     << std::endl;
    // std::cerr << "L\n"  << la::round(L)     << std::endl;
    // std::cerr << "U\n"  << la::round(U)     << std::endl;
    // std::cerr << "LU\n" << la::round(L * U) << std::endl;
    REQUIRE(approxEqual(A, L * U));
}