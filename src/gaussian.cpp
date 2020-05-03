#include "inc/gaussian.h"
#include "inc/util.h"
#include <utility>
#include <cmath>
#include <cassert>

namespace la
{

/**
 * Performs Gaussian elimination on A in place.
 * Involves applying elementary row operations on A until A is in reduced echelon form.
 * Uses row normalization and partial pivoting for numerical stability.
 */
void eliminate(Matrix& A, float epsilon)
{
    normalizeRows(A, epsilon);
    forwardReduce(A, 0, 0, epsilon);
    backwardReduce(A, A.rows() - 1, A.cols() - 1, epsilon);
}

/**
 * Scales each row such that the largest absolute value in the row is 1.
 */
void normalizeRows(Matrix& A, float epsilon)
{
    for (int i = 0; i < A.rows(); ++i)
    {
        float maxVal = 0.0F;
        for (int j = 0; j < A.cols(); ++j)
        {
            maxVal = std::max(maxVal, std::abs(A[j][i]));
        }
        if (!approxEqual(maxVal, 0.0F, epsilon))
        {
            scaleRow(A, i, 1.0F / maxVal);
        }
    }
}

/**
 * Reduces submatrix of A having top-left position (i, j)
 * to echelon form.
 */
void forwardReduce(Matrix& A, int i, int j, float epsilon)
{
    if (i == A.rows() || j == A.cols())
    {
        return;
    }
    float maxVal = 0.0F;
    int pivot = -1;  // row of entry with largest abs val in submatrix column j
    for (int k = i; k < A.rows(); ++k)
    {
        float val = std::abs(A[j][k]);
        if (val > maxVal && !approxEqual(val, 0.0F, epsilon))
        {
            maxVal = val;
            pivot = k;
        }
    }
    if (pivot == -1)
    {
        forwardReduce(A, i, j + 1, epsilon);
    }
    else
    {
        swapRows(A, i, pivot);

        // Use pivot element to create zeros below it.
        for (int k = i + 1; k < A.rows(); ++k)
        {
            replaceRow(A, k, i, -A[j][k] / A[j][i]);
            assert(approxEqual(A[j][k], 0.0F, epsilon));
        }

        forwardReduce(A, i + 1, j + 1, epsilon);
    }
}

/**
 * Reduces submatrix of (assumed echelon) matrix A having
 * bottom-right position (i, j) to reduced echelon form.
 */
void backwardReduce(Matrix& A, int i, int j, float epsilon)
{
    if (i < 0 || j < 0)
    {
        return;
    }
    int pivot = -1;  // column of first non-zero entry in submatrix row i
    for (int k = j; k >= 0; --k)
    {
        if (!approxEqual(A[k][i], 0.0F, epsilon))
        {
            pivot = k;
        }
    }
    if (pivot == -1)
    {
        backwardReduce(A, i - 1, j, epsilon);
    }
    else
    {
        // Use pivot element to create zeros above it.
        for (int k = i - 1; k >= 0; --k)
        {
            replaceRow(A, k, i, -A[pivot][k] / A[pivot][i]);
            assert(approxEqual(A[pivot][k], 0.0F, epsilon));
        }

        scaleRow(A, i, 1.0F / A[pivot][i]);
        assert(approxEqual(A[pivot][i], 1.0F, epsilon));
        backwardReduce(A, i - 1, pivot - 1, epsilon);
    }
}

void swapRows(Matrix& A, int i1, int i2)
{
    for (int j = 0; j < A.cols(); ++j)
    {
        std::swap(A[j][i1], A[j][i2]);
    }
    // std::cerr << "swap R" << i1 << " and R" << i2 << std::endl;
    // std::cerr << A << std::endl;
}

void scaleRow(Matrix& A, int i, float f)
{
    for (int j = 0; j < A.cols(); ++j)
    {
        A[j][i] *= f;
    }
    // std::cerr << "scale R" << i << " by " << f << '\n';
    // std::cerr << A << std::endl;
}

void replaceRow(Matrix& A, int i1, int i2, float f, int lo)
{
    assert(lo >= 0);
    for (int j = lo; j < A.cols(); ++j)
    {
        A[j][i1] += f * A[j][i2];
    }
    // std::cerr << "replace R" << i1 << " with R" << i1 << " + (" << f << " * R" << i2 << ")\n";
    // std::cerr << A << std::endl;
}

}  // namespace la