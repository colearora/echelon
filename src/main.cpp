#include "inc/vector.h"
// #include "inc/matrix.h"
#include <iostream>

int main()
{
    // la::Matrix A(4, 4);
    // A(0, 0) = 1234.5;
    // A(0, 1) = -987654321.1234567;
    // std::cout << A << std::endl;

    la::Vector<float, 4> v;
    v(0) = 1.3;
    v(3) = 1.67;
    std::cerr << v.dim() << std::endl;
}