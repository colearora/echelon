#ifndef LA_UTIL_H
#define LA_UTIL_H

#include "inc/rational.h"
#include <limits>

namespace la
{

bool approxEqual(float x, float y, float epsilon = std::numeric_limits<float>::epsilon());
bool approxEqual(double x, double y, double epsilon = std::numeric_limits<double>::epsilon());
bool approxEqual(Rational x, Rational y);

}  // namespace la

#endif