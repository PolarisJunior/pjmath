
#pragma once

#include "mat.hpp"
#include "math_defs.hpp"

namespace pjmath
{
  /**
   * @brief 3x3 Matrix type
   */
  class Mat3 : public Mat<real_t, 3, 3, Mat3>
  {
  public:
    using Mat::Mat; ///< Inherit constructors
  };
}