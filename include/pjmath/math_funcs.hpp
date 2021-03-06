#pragma once

#include <math.h>

#include <cstdint>

#include "definitions.hpp"

namespace pjmath
{
  inline static real_t Cos(real_t x)
  {
    return ::cos(x);
  }

  inline static real_t Sin(real_t x)
  {
    return ::sin(x);
  }

  inline static real_t Tan(real_t x)
  {
    return ::tan(x);
  }

  inline static real_t Abs(real_t x)
  {
    return fabs(x);
  }

  inline static int32_t Abs(int32_t x)
  {
    return abs(x);
  }

  inline static real_t ToRads(real_t degs)
  {
    return degs * 2.f * PI / 360.f;
  }
} // namespace pjmath
