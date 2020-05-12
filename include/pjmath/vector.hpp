#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <type_traits>

#include "math_defs.hpp"

/**
 * To create a vector of size N, use `Vector<N> vec{...}`
 * All operations which are valid on a `std::array` are valid
 * on a `Vector` of the same dimension.
 */
namespace pjmath {

template <std::size_t N, typename ValueType = real_t>
class Vector : public std::array<ValueType, N> {
 public:
  Vector& operator+=(const Vector& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::plus<ValueType>());
    return *this;
  }

  Vector operator+(const Vector& other) const { return Vector(*this) += other; }

  Vector& operator-=(const Vector& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::minus<ValueType>());
    return *this;
  }

  Vector operator-(const Vector& other) const { return Vector(*this) -= other; }

  Vector& operator*=(const Vector& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::multiplies<ValueType>());
    return *this;
  }

  Vector operator*(const Vector& other) const { return Vector(*this) *= other; }

  Vector& operator*=(ValueType scale) {
    std::transform(
        begin(), end(), begin(),
        std::bind(std::multiplies<ValueType>(), scale, std::placeholders::_1));
    return *this;
  }

  Vector operator*(ValueType scale) const { return Vector(*this) *= scale; }

  Vector& operator/=(const Vector& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::divides<ValueType>());
    return *this;
  }

  Vector operator/(const Vector& other) const { return Vector(*this) /= other; }

  Vector& operator/=(ValueType factor) {
    std::transform(
        begin(), end(), begin(),
        std::bind(std::divides<ValueType>(), std::placeholders::_1, factor));
    return *this;
  }

  Vector operator/(ValueType factor) { return Vector(*this) /= factor; }

  ValueType Dot(const Vector& other) const {
    return std::inner_product(begin(), end(), other.begin(), 0.0);
  }

  ValueType NormSquared() const { return Dot(*this); }

  ValueType Norm() const { return std::sqrt(NormSquared()); }

  Vector Normalized() const { return Vector(*this).Normalize(); }

  Vector& Normalize() {
    ValueType norm = Norm();
    return norm <= 0 ? *this : *this /= norm;
  }

  ValueType& X() { return std::get<0>(*this); }
  ValueType& Y() { return std::get<1>(*this); }
  ValueType& Z() { return std::get<2>(*this); }

  ValueType X() const { return std::get<0>(*this); }
  ValueType Y() const { return std::get<1>(*this); }
  ValueType Z() const { return std::get<2>(*this); }

  static Vector One() {
    Vector ret;
    std::fill(ret.begin(), ret.end(), 1);
    return ret;
  }

  static Vector Zero() { return Vector{}; }

  template <std::size_t N = N,
            typename ValueType = ValueType,
            typename std::enable_if<N == 3, int>::type = 0>
  Vector Cross(const Vector& other) const {
    return Vector3{Y() * other.Z() - Z() * other.Y(),
                   Z() * other.X() - X() * other.Z(),
                   X() * other.Y() - Y() * other.X()};
  }

  template <std::size_t N = N,
            typename ValueType = ValueType,
            typename std::enable_if<N == 3, int>::type = 0>
  static Vector Up() {
    return {0, 1, 0};
  }

  template <std::size_t N = N,
            typename ValueType = ValueType,
            typename std::enable_if<N == 3, int>::type = 0>
  static Vector Down() {
    return {0, -1, 0};
  }

  template <std::size_t N = N,
            typename ValueType = ValueType,
            typename std::enable_if<N == 3, int>::type = 0>
  static Vector Right() {
    return {1, 0, 0};
  }

  template <std::size_t N = N,
            typename ValueType = ValueType,
            typename std::enable_if<N == 3, int>::type = 0>
  static Vector Left() {
    return {-1, 0, 0};
  }

  template <std::size_t N = N,
            typename ValueType = ValueType,
            typename std::enable_if<N == 3, int>::type = 0>
  static Vector Forward() {
    return {0, 0, 1};
  }

  template <std::size_t N = N,
            typename ValueType = ValueType,
            typename std::enable_if<N == 3, int>::type = 0>
  static Vector Backward() {
    return {0, 0, -1};
  }
};

using Vector2 = Vector<2>;
using Vector3 = Vector<3>;
using Vector4 = Vector<4>;

}  // namespace pjmath
