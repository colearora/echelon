#ifndef LA_GAUSSIAN_H
#define LA_GAUSSIAN_H

#include "inc/matrix.h"
#include <limits>

namespace la
{

// Gaussian elimination:
void eliminate(Matrix& A, float epsilon = std::numeric_limits<float>::epsilon());

void normalizeRows(Matrix& A, float epsilon);
void forwardReduce(Matrix& A, int i, int j, float epsilon);
void backwardReduce(Matrix& A, int i, int j, float epsilon);

// Elementary row operations:
void swapRows(Matrix& A, int i1, int i2);
void scaleRow(Matrix& A, int i, float f);
void replaceRow(Matrix& A, int i1, int i2, float f, int lo = 0);

}  // namespace la

#endif