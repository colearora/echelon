#include "inc/vector.h"
#include "inc/matrix.h"
#include "inc/gaussian.h"
#include <iostream>

int main() {
    la::Matrix A = la::Matrix::fromRows({
        {1, 2, 3, 4},
        {4, 5, 6, 7},
        {6, 7, 8, 9}});
    la::eliminate(A);
    std::cout << la::round(A) << std::endl;
    // REQUIRE(la::approxEqual(A, la::Matrix{
    //     {1, 0, -1, -2},
    //     {0, 1,  2,  3},
    //     {0, 0,  0,  0}}));
}