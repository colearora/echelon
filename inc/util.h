#ifndef LA_UTIL_H
#define LA_UTIL_H

#include <limits>

namespace la {

bool approxEqual(float x, float y, float epsilon = std::numeric_limits<float>::epsilon());

}  // namespace la

#endif