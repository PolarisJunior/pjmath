#pragma once

#include <math.h>

#include <cstdint>

#include "math_defs.hpp"

class Math {
 public:
  static real_t Cos(real_t x) { return ::cos(x); }
  static real_t Sin(real_t x) { return ::sin(x); }
  static real_t Tan(real_t x) { return ::tan(x); }

  static real_t Abs(real_t x) { return fabs(x); }
  static int32_t Abs(int32_t x) { return abs(x); }

  static real_t ToRads(real_t degs) { return degs * 2.f * PI / 360.f; }
};
