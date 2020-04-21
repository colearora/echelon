#ifndef LA_GAUSSIAN_H
#define LA_GAUSSIAN_H

#include "inc/matrix.h"

namespace la {

// Gaussian elimination:
void eliminate(Matrix& A);

void normalizeRows(Matrix& A);
void forwardReduce(Matrix& A, int i, int j);
void backwardReduce(Matrix& A, int i, int j);

// Elementary row operations:
void swapRows(Matrix& A, int i1, int i2);
void scaleRow(Matrix& A, int i, float f);
void replaceRow(Matrix& A, int i1, int i2, float f);

}  // namespace la

#endif