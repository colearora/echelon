#include "inc/util.h"
#include <cmath>  // abs()
#include <cassert>

namespace la
{

bool approxEqual(float x, float y, float epsilon) {
    return std::abs(x - y) <= (std::abs(x) + std::abs(y) + 1.0F) * epsilon;
}

bool approxEqual(double x, double y, double epsilon) {
    return std::abs(x - y) <= (std::abs(x) + std::abs(y) + 1.0) * epsilon;
}

bool approxEqual(Rational x, Rational y) {
    return x == y;
}

}  // namespace la