#include "inc/util.h"
#include <cmath>  // abs()

namespace la
{

/**
 * approxEqual: returns true if the relative error between the
 * floating-point inputs a and b is less than or equal to some
 * tolerance, false otherwise.
 */
bool approxEqual(float a, float b, float epsilon)
{
    return std::abs(a - b) <= (std::abs(a) + std::abs(b) + 1.0f) * epsilon;
}

}  // namespace la