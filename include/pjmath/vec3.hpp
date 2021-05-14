
#pragma once

#include "mat.hpp"
#include "definitions.hpp"

namespace pjmath
{

  /**
   * @brief 3-dimensional vector type
   */
  class Vec3 : public Mat<real_t, 3, 1, Vec3>
  {
  public:
    using Mat::Mat; ///< Inherit constructors

    constexpr const real_t &x() const
    {
      return at(0);
    }

    constexpr const real_t &y() const
    {
      return at(1);
    }

    constexpr const real_t &z() const
    {
      return at(2);
    }

    real_t &x()
    {
      return at(0);
    }

    real_t &y()
    {
      return at(1);
    }

    real_t &z()
    {
      return at(2);
    }
  };

}
