#pragma once

namespace la
{

constexpr float DEFAULT_EPSILON = 1e-5F;

bool approxEqual(float x, float y, float epsilon = DEFAULT_EPSILON);

}  // namespace la
