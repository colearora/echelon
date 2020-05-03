#ifndef LA_FACTOR_H
#define LA_FACTOR_H

#include "inc/matrix.h"

namespace la
{

void factor(const Matrix& A, int (*pivotSelector)(const Vector&, int*),
            Matrix& L, Matrix& U);

int partialPivotSelector(const Vector& c, int* rowMap);
int firstNonzeroPivotSelector(const Vector& c, int* rowMap);
void permute(const Matrix& V, int* rowMap, Matrix& U);

}  // namespace la

#endif