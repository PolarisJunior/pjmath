#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>

#include "math_defs.hpp"

/**
 * To create a vector of size N, use `Vector<N> vec{...}`
 * All operations which are valid on a `std::array` are valid
 * on a `Vector` of the same dimension.
 */
namespace pjmath {

template <std::size_t N, typename ValueType, typename VectorType>
class VectorBase : public std::array<ValueType, N> {
 public:
  VectorType& operator+=(const VectorType& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::plus<ValueType>());
    return *static_cast<VectorType*>(this);
  }

  VectorType operator+(const VectorType& other) const {
    return VectorType(*static_cast<const VectorType*>(this)) += other;
  }

  VectorType& operator-=(const VectorType& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::minus<ValueType>());
    return *static_cast<VectorType*>(this);
  }

  VectorType operator-(const VectorType& other) const {
    return VectorType(*static_cast<const VectorType*>(this)) -= other;
  }

  VectorType& operator*=(const VectorType& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::multiplies<ValueType>());
    return *static_cast<VectorType*>(this);
  }

  VectorType operator*(const VectorType& other) const {
    return VectorType(*static_cast<const VectorType*>(this)) *= other;
  }

  VectorType& operator*=(ValueType scale) {
    std::transform(
        begin(), end(), begin(),
        std::bind(std::multiplies<ValueType>(), scale, std::placeholders::_1));
    return *static_cast<VectorType*>(this);
  }

  VectorType operator*(ValueType scale) const {
    return VectorType(*static_cast<const VectorType*>(this)) *= scale;
  }

  VectorType& operator/=(const VectorType& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::divides<ValueType>());
    return *static_cast<VectorType*>(this);
  }

  VectorType operator/(const VectorType& other) const {
    return VectorType(*static_cast<const VectorType*>(this)) /= other;
  }

  VectorType& operator/=(ValueType factor) {
    std::transform(
        begin(), end(), begin(),
        std::bind(std::divides<ValueType>(), std::placeholders::_1, factor));
    return *static_cast<VectorType*>(this);
  }

  VectorType operator/(ValueType factor) {
    return VectorType(*static_cast<const VectorType*>(this)) /= factor;
  }

  ValueType Dot(const VectorBase& other) const {
    return std::inner_product(begin(), end(), other.begin(), 0.0);
  }

  ValueType NormSquared() const { return Dot(*this); }

  ValueType Norm() const { return std::sqrt(NormSquared()); }

  VectorType Normalized() const {
    return VectorType(*static_cast<const VectorType*>(this)).Normalize();
  }

  VectorType& Normalize() {
    ValueType norm = Norm();
    return norm <= 0 ? *static_cast<VectorType*>(this)
                     : *static_cast<VectorType*>(this) /= norm;
  }

  static const VectorType zero;
  static const VectorType one;
};

template <std::size_t N, typename ValueType, typename VectorType>
const VectorType VectorBase<N, ValueType, VectorType>::zero{};

template <std::size_t N, typename ValueType, typename VectorType>
const VectorType VectorBase<N, ValueType, VectorType>::one = ([]() {
  VectorType ret;
  std::fill(ret.begin(), ret.end(), 1);
  return ret;
})();

template <std::size_t N>
class Vector : public VectorBase<N, real_t, Vector<N>> {};

class Vector2 : public VectorBase<2, real_t, Vector2> {
 public:
  real_t& x = std::get<0>(*this);
  real_t& y = std::get<1>(*this);
};

class Vector3 : public VectorBase<3, real_t, Vector3> {
 public:
  real_t& x = std::get<0>(*this);
  real_t& y = std::get<1>(*this);
  real_t& z = std::get<2>(*this);

  Vector3 Cross(const Vector3& other) const noexcept {
    return Vector3{y * other.z - z * other.y, z * other.x - x * other.z,
                   x * other.y - y * other.x};
  }

  real_t Pitch() const noexcept { return x; }
  real_t Yaw() const noexcept { return y; }
  real_t Roll() const noexcept { return z; }

  const static Vector3 right;
  const static Vector3 left;
  const static Vector3 up;
  const static Vector3 down;
  const static Vector3 front;
  const static Vector3 back;
  const static Vector3 forward;
  const static Vector3 backward;
};

class Vector4 : public VectorBase<4, real_t, Vector4> {
 public:
  real_t& x = std::get<0>(*this);
  real_t& y = std::get<1>(*this);
  real_t& z = std::get<2>(*this);
  real_t& w = std::get<3>(*this);
};

const Vector3 Vector3::right = Vector3{1, 0, 0};
const Vector3 Vector3::left = Vector3{-1, 0, 0};
const Vector3 Vector3::up = Vector3{0, 1, 0};
const Vector3 Vector3::down = Vector3{0, -1, 0};
const Vector3 Vector3::forward = Vector3{0, 0, 1};
const Vector3 Vector3::backward = Vector3{0, 0, -1};

}  // namespace pjmath
