#include "inc/vector.h"
#include "inc/matrix.h"
#include "inc/gaussian.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

int main() {
    // la::Matrix A = la::Matrix::fromRows({
    //     {0, 1, 1, -1, 0, 0, -1, 0, 0, 0},
    //     {1, 1, 4, 0, -1, 0, 0, -1, 0, 0},
    //     {1, 3, 4, 0, 0, -1, 0, 0, -1, 0},
    //     {1, 0, 0, 1, -1, -1, 3, 0, 0, 0},
    //     {0, 1, 0, -1, 0, -4, 0, 3, 0, 0},
    //     {0, 0, 1, -1, -3, -3, 0, 0, 3, 0},
    //     {1, 0, 0, 4, 0, 0, 4, -1, -1, 0},
    //     {0, 1, 0, 0, 4, 0, -1, 3, -4, 0},
    //     {0, 0, 1, 0, 0, 4, -1, -3, 0, 0}});
    // la::eliminate(A);
    // std::cout << la::round(A) << std::endl;

    la::Matrix A = la::Matrix::fromRows({
        {1.0F / 6, 1.0F / 2, 1.0F / 3},
        {1.0F / 2, 1.0F / 4, 1.0F / 4},
        {1.0F / 3, 1.0F / 4, 5.0F / 12}});
    for (int k = 1; k <= 30; ++k) {
        std::cout << "A^" << k << ":\n" << la::pow(A, k) << std::endl;
    }
}

