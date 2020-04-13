#include "inc/util.h"
#include <cmath>  // abs()
#include <cassert>

namespace la {

bool approxEqual(float x, float y, float epsilon) {
    return std::abs(x - y) <= (std::abs(x) + std::abs(y) + 1.0F) * epsilon;
}

}  // namespace la