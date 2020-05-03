#include "inc/catch.h"
#include "inc/factor.h"
#include <iostream>

TEST_CASE("factor: 4x4 A without interchanges", "[factor]")
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
    // std::cout << "A\n"  << la::round(A)     << std::endl;
    // std::cout << "L\n"  << la::round(L)     << std::endl;
    // std::cout << "U\n"  << la::round(U)     << std::endl;
    // std::cout << "LU\n" << la::round(L * U) << std::endl;
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

TEST_CASE("factor: 4x5 A with interchanges and no zero rows", "[factor]")
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
    // std::cout << "A\n"  << la::round(A)     << std::endl;
    // std::cout << "L\n"  << la::round(L)     << std::endl;
    // std::cout << "U\n"  << la::round(U)     << std::endl;
    // std::cout << "LU\n" << la::round(L * U) << std::endl;
    REQUIRE(approxEqual(A, L * U));
}

TEST_CASE("factor: 5x4 A with interchanges and two zero rows", "[factor]")
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
    // std::cout << "A\n"  << la::round(A)     << std::endl;
    // std::cout << "L\n"  << la::round(L)     << std::endl;
    // std::cout << "U\n"  << la::round(U)     << std::endl;
    // std::cout << "LU\n" << la::round(L * U) << std::endl;
    REQUIRE(approxEqual(A, L * U));
}