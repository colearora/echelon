#include "inc/gauss.h"
#include "inc/util.h"
#include <algorithm>  // min()
#include <utility>
#include <cmath>
#include <cassert>

namespace la
{

/**
 * Applies Gaussian elimination to A.
 * On return, A is in reduced echelon form.
 */
void eliminate(Matrix& A,
               int (*pivotSelector)(const Vector&, const std::set<int>&))
{
    forwardReduce(A, pivotSelector);
    backwardReduce(A);
}

/**
 * Applies row operations to A.
 * On return, A is in echelon form.
 */
void forwardReduce(Matrix& A,
                   int (*pivotSelector)(const Vector&, const std::set<int>&))
{
    Matrix temp(A.rows(), A.rows());
    Matrix U(A.rows(), A.cols());
    factor(A, pivotSelector, temp, U);
    A = U;
}

/**
 * Applies row operations to (assumed echelon) U.
 * On return, U is in reduced echelon form.
 */
void backwardReduce(Matrix& U)
{
    for (int i = U.rows() - 1, j = U.cols() - 1; i >= 0 && j >= 0; )
    {
        // Update j to column index of leftmost nonzero entry of row i.
        // Take the entry at row i and column j as pivot.
        int pivotCol = 0;
        while (pivotCol <= j && approxEqual(U[pivotCol][i], 0.0F))
        {
            ++pivotCol;
        }
        if (pivotCol > j)
        {
            // Non-pivot (zero) row.
            --i;
            continue;
        }
        j = pivotCol;

        // Use pivot to create zeros above it.
        for (int k = i - 1; k >= 0; --k)
        {
            replaceRow(U, k, i, -U[j][k] / U[j][i], j);
        }

        // Scale ith row such that pivot is 1.
        scaleRow(U, i, 1.0F / U[j][i], j);

        --i;
        --j;
    }
}

/**
 * Applies LU factorization to m x n matrix A.
 * On return, L is (m x m) permuted unit lower triangular,
 * U is an echelon form of A, and A = LU.
 */
void factor(const Matrix& A,
            int (*pivotSelector)(const Vector&, const std::set<int>&),
            Matrix& L, Matrix& U)
{
    int m = A.rows(), n = A.cols();
    assert(L.rows() == m && L.cols() == m);
    assert(U.rows() == m && U.cols() == n);

    L *= 0.0F;
    Matrix V = A;
    std::map<int, int> perm;  // row i of V corresponds to row perm[i] of U
    std::set<int> rows;  // tracks rows not yet covered
    for (int i = 0; i < m; ++i)
    {
        rows.insert(i);
    }

    // Reduce V to a permuted echelon form of A while filling in L.
    int pivotCount = 0;
    for (int j = 0; j < n && pivotCount < std::min(m, n); ++j)
    {
        int pivotRow = (*pivotSelector)(V[j], rows);
        if (pivotRow == -1)
        {
            continue;  // zero column
        }
        perm[pivotRow] = pivotCount;
        rows.erase(pivotRow);
        L[pivotCount][pivotRow] = 1.0F;
        for (int i : rows)
        {
            L[pivotCount][i] = V[j][i] / V[j][pivotRow];
            replaceRow(V, i, pivotRow, -V[j][i] / V[j][pivotRow], j);
        }
        ++pivotCount;
    }

    // Handle any non-pivot (zero) rows in V.
    for (int i : rows)
    {
        L[pivotCount][i] = 1.0F;
        perm[i] = pivotCount;
        ++pivotCount;
    }

    // Fill in U from V and the recorded permutation.
    permute(V, perm, U);
}

void permute(const Matrix& V, const std::map<int, int>& perm, Matrix& U)
{
    assert(V.rows() == U.rows() && V.cols() == U.cols());
    assert(V.rows() == perm.size());

    for (const auto& pair : perm)
    {
        assert(pair.first >= 0 && pair.first <= V.rows());
        assert(pair.second >= 0 && pair.second <= U.rows());
        for (int j = 0; j < V.cols(); ++j)
        {
            U[j][pair.second] = V[j][pair.first];
        }
    }
}

int partialPivotSelector(const Vector& c, const std::set<int>& rows)
{
    float maxVal = 0.0F;
    int pivotRow = -1;
    for (int i : rows)
    {
        assert(i >= 0 && i < c.size());
        float val = std::abs(c[i]);
        if (val > maxVal && !approxEqual(val, 0.0F))
        {
            maxVal = val;
            pivotRow = i;
        }
    }
    return pivotRow;
}

int firstNonzeroPivotSelector(const Vector& c, const std::set<int>& rows)
{
    for (int i : rows)
    {
        assert(i >= 0 && i < c.size());
        if (!approxEqual(c[i], 0.0F))
        {
            return i;
        }
    }
    return -1;
}

void swapRows(Matrix& A, int i1, int i2, int lo)
{
    assert(i1 >= 0 && i1 < A.rows());
    assert(i2 >= 0 && i2 < A.rows());
    assert(lo >= 0);

    if (i1 == i2)
    {
        return;
    }
    for (int j = lo; j < A.cols(); ++j)
    {
        std::swap(A[j][i1], A[j][i2]);
    }
    // std::cerr << "swap R" << i1 << " and R" << i2 << std::endl;
    // std::cerr << A << std::endl;
}

void scaleRow(Matrix& A, int i, float f, int lo)
{
    assert(i >= 0 && i < A.rows());
    assert(lo >= 0);

    for (int j = lo; j < A.cols(); ++j)
    {
        A[j][i] *= f;
    }
    // std::cerr << "scale R" << i << " by " << f << '\n';
    // std::cerr << A << std::endl;
}

void replaceRow(Matrix& A, int i1, int i2, float f, int lo)
{
    assert(i1 >= 0 && i1 < A.rows());
    assert(i2 >= 0 && i2 < A.rows());
    assert(lo >= 0);

    for (int j = lo; j < A.cols(); ++j)
    {
        A[j][i1] += f * A[j][i2];
    }
    // std::cerr << "replace R" << i1 << " with R" << i1;
    // std::cerr << " + (" << f << " * R" << i2 << ")\n";
    // std::cerr << A << std::endl;
}

}  // namespace la
