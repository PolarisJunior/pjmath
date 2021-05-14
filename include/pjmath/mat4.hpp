
#pragma once

#include "mat.hpp"
#include "definitions.hpp"

namespace pjmath
{
  /**
   * @brief 4x4 matrix type
   */
  class Mat4 : public Mat<real_t, 4, 4, Mat4>
  {
  public:
    using Mat::Mat; ///< Inherit constructors
  };

}