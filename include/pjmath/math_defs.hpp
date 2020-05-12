
#pragma once

#ifdef REAL_T_IS_DOUBLE
typedef double real_t;
#else
typedef float real_t;
#endif

namespace pjmath {
constexpr real_t CMP_EPSILON = 0.00001;
constexpr real_t PI = 3.14159265f;
}  // namespace pjmath
