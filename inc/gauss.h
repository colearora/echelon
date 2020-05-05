#pragma once

#include "inc/vector.h"
#include "inc/matrix.h"
#include <set>
#include <map>

namespace la
{

// Gaussian elimination
void eliminate(Matrix& A, int (*)(const Vector&, const std::set<int>&));
void forwardReduce(Matrix& A, int (*)(const Vector&, const std::set<int>&));
void backwardReduce(Matrix& U);

// LU factorization
void factor(const Matrix& A, int (*)(const Vector&, const std::set<int>&),
            Matrix& L, Matrix& U);
void permute(const Matrix& V, const std::map<int, int>& perm, Matrix& U);

// Pivot selectors
int partialPivotSelector(const Vector& c, const std::set<int>& rows);
int firstNonzeroPivotSelector(const Vector& c, const std::set<int>& rows);

// Elementary row operations
void swapRows(Matrix& A, int i1, int i2, int lo = 0);
void scaleRow(Matrix& A, int i, float f, int lo = 0);
void replaceRow(Matrix& A, int i1, int i2, float f, int lo = 0);

}  // namespace la