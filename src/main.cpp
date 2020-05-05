#include "inc/vector.h"
#include "inc/matrix.h"
#include "inc/gauss.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

int main()
{
    // la::Matrix A = la::Matrix::fromRows(
    //     {
    //         {0, 1, 1, -1, 0, 0, -1, 0, 0, 0},
    //         {1, 1, 4, 0, -1, 0, 0, -1, 0, 0},
    //         {1, 3, 4, 0, 0, -1, 0, 0, -1, 0},
    //         {1, 0, 0, 1, -1, -1, 3, 0, 0, 0},
    //         {0, 1, 0, -1, 0, -4, 0, 3, 0, 0},
    //         {0, 0, 1, -1, -3, -3, 0, 0, 3, 0},
    //         {1, 0, 0, 4, 0, 0, 4, -1, -1, 0},
    //         {0, 1, 0, 0, 4, 0, -1, 3, -4, 0},
    //         {0, 0, 1, 0, 0, 4, -1, -3, 0, 0}
    //     });
    // la::eliminate(A, la::partialPivotSelector);
    // std::cout << la::round(A) << std::endl;

    // la::Matrix A = la::Matrix::fromRows(
    //     {
    //         {1.0F / 6, 1.0F / 2, 1.0F / 3},
    //         {1.0F / 2, 1.0F / 4, 1.0F / 4},
    //         {1.0F / 3, 1.0F / 4, 5.0F / 12}
    //     });
    // for (int k = 1; k <= 30; ++k)
    // {
    //     std::cout << "A^" << k << ":\n" << la::pow(A, k) << std::endl;
    // }

    la::Vector y{0.08F, 0.12F, 0.16F, 0.12F};
    la::Matrix D = la::Matrix::fromRows(
        {
            {0.0040F, 0.0030F, 0.0010F, 0.0005F},
            {0.0030F, 0.0050F, 0.0030F, 0.0010F},
            {0.0010F, 0.0030F, 0.0050F, 0.0030F},
            {0.0005F, 0.0010F, 0.0030F, 0.0040F}
        });
    la::Matrix DInv(D.rows(), D.cols());
    bool invertible = la::inverse(D, DInv);
    if (invertible)
    {
        std::cout << DInv * y << std::endl;
    }
}

