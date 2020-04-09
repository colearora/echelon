#ifndef LA_GAUSSIAN_H
#define LA_GAUSSIAN_H

#include "inc/matrix.h"

namespace la
{

/**
 * Gaussian: an encapsulation of the Gaussian elimination algorithm,
 * which operates on an augmented matrix representing the coefficients
 * of a linear system of equations.
 */
class Gaussian
{
public:
    static void eliminate(Matrix& A);

private:
    static void forwardReduce(Matrix& A, int r, int c);
    static void backwardReduce(Matrix& A, int r, int c);
};

}  // namespace la

#endif