#pragma once

#include "mat.hpp"
#include "definitions.hpp"

namespace pjmath
{
  /**
   * @brief 4 dimensional vector type
   */
  class Vec4 : public Mat<real_t, 4, 1, Vec4>
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

    constexpr const real_t &w() const
    {
      return at(3);
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

    real_t &w()
    {
      return at(3);
    }
  };

}