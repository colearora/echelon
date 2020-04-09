#include "inc/gaussian.h"
#include "inc/util.h"  // approxEqual()
#include <cassert>
#include <cmath>

namespace la
{

/* eliminate: applies elementary row operations until A is in reduced echelon form. */
void Gaussian::eliminate(Matrix& A)
{
    forwardReduce(A, 0, 0);
    backwardReduce(A, A.rows() - 1, A.cols() - 2);  // -2 skips right-most col of aug matrix
}

/* forwardReduce: transforms submatrix A[r..m-1][c..n-1] to echelon form. */
void Gaussian::forwardReduce(Matrix& A, int r, int c)
{
    if (r == A.rows() || c == A.cols())
    {
        return;
    }

    // Find the row index of the element in column c having largest absolute value.
    // To improve stability this element will be taken as the pivot element for this column.
    float maxVal = 0.0F;
    int pr = -1;  // pivot row
    for (int i = r; i < A.rows(); ++i)
    {
        float val = std::fabs(A(i, c));
        if (val > maxVal)
        {
            maxVal = val;
            pr = i;
        }
    }

    if (pr == -1)
    {
        // No pivot in column c -- skip the column.
        forwardReduce(A, r, c + 1);
    }
    else
    {
        // Move the pivot element to the top of the submatrix.
        A.swapRows(r, pr);

        // Use the pivot element to create zeros below it in column c.
        for (int i = r + 1; r < A.rows(); ++i)
        {
            float f = -A(i, c) / A(r, c);
            A.replaceRow(i, r, f);
            assert(approxEqual(A(i, c), 0.0F));
        }

        forwardReduce(A, r + 1, c + 1);
    }
}

/* backwardReduce: transforms echelon submatrix A[0..r][0..c] to reduced echelon form. */
void Gaussian::backwardReduce(Matrix& A, int r, int c)
{
    if (r < 0 || c < 0)
    {
        return;
    }
    
    // Scan left to find the leading element of row r if any.
    int pc = -1;  // pivot column
    for (int j = c; j >= 0; --j)
    {
        if (!approxEqual(A(r, j), 0.0F))
        {
            pc = j;
        }
    }
    
    if (pc == -1)
    {
        // Row r has no pivot -- skip the row.
        backwardReduce(A, r - 1, c);
    }
    else
    {
        // Use pivot element A(r, pc) to create zeros above it in column pc.
        for (int i = r - 1; i >= 0; --i)
        {
            float f = -A(i, pc) / A(r, pc);
            A.replaceRow(i, r, f);
            assert(approxEqual(A(i, pc), 0.0F));
        }
        
        // Scale row r such that the pivot element is 1.
        A.scaleRow(r, 1.0F / A(r, pc));
        assert(approxEqual(A(r, pc), 1.0F));
        
        backwardReduce(A, r - 1, pc - 1);
    }
}

}  // namespace la