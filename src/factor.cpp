#include "inc/factor.h"
#include "inc/util.h"
#include "inc/gaussian.h"  // replaceRow()
#include <algorithm>  // min()
#include <cassert>

namespace la
{

/**
 * Applies LU factorization to m x n matrix A.
 * On return, L is (m x m) permuted unit lower triangular,
 * U is an echelon form of A, and A = LU.
 */
void factor(const Matrix& A, int (*pivotSelector)(const Vector&, int*),
            Matrix& L, Matrix& U)
{
    int m = A.rows(), n = A.cols();
    assert(L.rows() == m && L.cols() == m);
    assert(U.rows() == m && U.cols() == n);

    L *= 0.0F;
    Matrix V = A;
    int rowMap[m];  // row i of V corresponds to row rowMap[i] of U
    for (int i = 0; i < m; ++i)
        rowMap[i] = -1;

    // Reduce V to a permuted echelon form of A while filling in L.
    int pivotCount = 0;
    for (int j = 0; j < n && pivotCount < std::min(m, n); ++j)
    {
        int pivotRow = (*pivotSelector)(V[j], rowMap);
        if (pivotRow == -1) continue;  // zero column
        for (int i = 0; i < m; ++i)
        {
            if (rowMap[i] != -1) continue;
            L[pivotCount][i] = V[j][i] / V[j][pivotRow];
            if (i != pivotRow)
                replaceRow(V, i, pivotRow, -V[j][i] / V[j][pivotRow], j);
        }
        rowMap[pivotRow] = pivotCount++;
    }

    // Handle any non-pivot (zero) rows in V.
    for (int i = 0; i < m; ++i)
    {
        if (rowMap[i] != -1) continue;
        L[pivotCount][i] = 1.0F;
        rowMap[i] = pivotCount++;
    }

    // Fill in U from V and rowMap.
    permute(V, rowMap, U);
}

int partialPivotSelector(const Vector& c, int* rowMap)
{
    float maxVal = 0.0F;
    int pivotRow = -1;
    for (int i = 0; i < c.size(); ++i)
    {
        if (rowMap && rowMap[i] != -1) continue;
        float val = std::abs(c[i]);
        if (val > maxVal && !approxEqual(val, 0.0F))
        {
            maxVal = val;
            pivotRow = i;
        }
    }
    return pivotRow;
}

int firstNonzeroPivotSelector(const Vector& c, int* rowMap)
{
    for (int i = 0; i < c.size(); ++i)
    {
        if (rowMap && rowMap[i] != -1) continue;
        if (!approxEqual(c[i], 0.0F)) return i;
    }
    return -1;
}

void permute(const Matrix& V, int* rowMap, Matrix& U)
{
    assert(V.rows() == U.rows() && V.cols() == U.cols());
    assert(rowMap != nullptr);

    for (int i = 0; i < V.rows(); ++i)
        for (int j = 0; j < V.cols(); ++j)
            U[j][rowMap[i]] = V[j][i];
}

}  // namespace la
