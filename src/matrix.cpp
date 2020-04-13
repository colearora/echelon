#include "inc/matrix.h"

namespace la {

Matrix::Matrix(std::size_t m, std::size_t n) : _m{m}, _n{n}, _c{new Vector*[n]} {
    for (std::size_t j = 0; j < n; ++j) {
        _c[j] = new Vector(m);
    }
}

Matrix Matrix::identity(int n) {
    Matrix I(n, n, 0.0F);
    for (std::size_t k = 0; k < n; ++k) {
        I(k, k) = 1.0F;
    }
    return I;
}

}  // namespace la