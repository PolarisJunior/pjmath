#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <type_traits>

#include "math_defs.hpp"

/**
 * To create a vector of size N, define a subclass
 * `class VectorN : public Vector<N, VectorN> {};`
 * All operations which are valid on a `std::array` are valid
 * on a `Vector` of the same dimension.
 *
 * In place operations that return `*this` rely on the property
 * of reinterpret_cast to not have any runtime overhead.
 *
 * When modifying this class, keep in mind separation of data and
 * operations on that data. The data is defined as the VectorBase/array
 * containing that data, so operations should be able to use arrays as
 * inputs.
 */
namespace pjmath {

template <std::size_t N,
          typename VectorType = nullptr_t,
          typename ValueType = real_t>
class Vector : public std::array<ValueType, N> {
  using VectorBase = std::array<ValueType, N>;

 public:
  VectorType& operator+=(const VectorBase& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::plus<ValueType>());
    return *reinterpret_cast<VectorType*>(this);
  }

  VectorType operator+(const VectorBase& other) const {
    return VectorType(*reinterpret_cast<const VectorType*>(this)) += other;
  }

  VectorType& operator-=(const VectorBase& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::minus<ValueType>());
    return *reinterpret_cast<VectorType*>(this);
  }

  VectorType operator-(const VectorBase& other) const {
    return VectorType(*reinterpret_cast<const VectorType*>(this)) -= other;
  }

  VectorType& operator*=(const VectorBase& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::multiplies<ValueType>());
    return *reinterpret_cast<VectorType*>(this);
  }

  VectorType operator*(const VectorBase& other) const {
    return VectorType(*reinterpret_cast<const VectorType*>(this)) *= other;
  }

  VectorType& operator*=(ValueType scale) {
    std::transform(
        begin(), end(), begin(),
        std::bind(std::multiplies<ValueType>(), scale, std::placeholders::_1));
    return *reinterpret_cast<VectorType*>(this);
  }

  VectorType operator*(ValueType scale) const {
    return VectorType(*reinterpret_cast<const VectorType*>(this)) *= scale;
  }

  VectorType& operator/=(const VectorBase& other) {
    std::transform(begin(), end(), other.begin(), begin(),
                   std::divides<ValueType>());
    return *reinterpret_cast<VectorType*>(this);
  }

  VectorType operator/(const VectorBase& other) const {
    return VectorType(*reinterpret_cast<const VectorType*>(this)) /= other;
  }

  VectorType& operator/=(ValueType factor) {
    std::transform(
        begin(), end(), begin(),
        std::bind(std::divides<ValueType>(), std::placeholders::_1, factor));
    return *reinterpret_cast<VectorType*>(this);
  }

  VectorType operator/(ValueType factor) {
    return VectorType(*reinterpret_cast<const VectorType*>(this)) /= factor;
  }

  ValueType Dot(const VectorBase& other) const {
    return std::inner_product(begin(), end(), other.begin(), 0.0);
  }

  ValueType NormSquared() const {
    return Dot(*reinterpret_cast<const VectorType*>(this));
  }

  ValueType Norm() const { return std::sqrt(NormSquared()); }

  VectorType Normalized() const {
    return VectorType(*reinterpret_cast<const VectorType*>(this)).Normalize();
  }

  VectorType& Normalize() {
    ValueType norm = Norm();
    return norm <= 0 ? *reinterpret_cast<VectorType*>(this)
                     : *reinterpret_cast<VectorType*>(this) /= norm;
  }
  template <std::size_t N_ = N,
            typename std::enable_if<(N_ >= 1), int>::type = 0>
  ValueType x() const {
    return std::get<0>(*reinterpret_cast<const VectorBase*>(this));
  }

  template <std::size_t N_ = N,
            typename std::enable_if<(N_ >= 1), int>::type = 0>
  ValueType& x() {
    return std::get<0>(*reinterpret_cast<VectorBase*>(this));
  }

  template <std::size_t N_ = N,
            typename std::enable_if<(N_ >= 2), int>::type = 0>
  ValueType y() const {
    return std::get<1>(*reinterpret_cast<const VectorBase*>(this));
  }

  template <std::size_t N_ = N,
            typename std::enable_if<(N_ >= 2), int>::type = 0>
  ValueType& y() {
    return std::get<1>(*reinterpret_cast<VectorBase*>(this));
  }

  template <std::size_t N_ = N,
            typename std::enable_if<(N_ >= 3), int>::type = 0>
  ValueType z() const {
    return std::get<2>(*reinterpret_cast<const VectorBase*>(this));
  }

  template <std::size_t N_ = N,
            typename std::enable_if<(N_ >= 3), int>::type = 0>
  ValueType& z() {
    return std::get<2>(*reinterpret_cast<VectorBase*>(this));
  }

  template <std::size_t N_ = N,
            typename std::enable_if<(N_ >= 4), int>::type = 0>
  ValueType w() const {
    return std::get<3>(*reinterpret_cast<VectorBase*>(this));
  }

  template <std::size_t N_ = N,
            typename std::enable_if<(N_ >= 4), int>::type = 0>
  ValueType& w() {
    return std::get<3>(*reinterpret_cast<VectorBase*>(this));
  }

  static VectorType One() {
    VectorType ret;
    std::fill(ret.begin(), ret.end(), 1);
    return ret;
  }

  static VectorType Zero() { return VectorType{}; }
};

class Vector2 : public Vector<2, Vector2> {};

class Vector3 : public Vector<3, Vector3> {
 public:
  Vector3 Cross(const Vector3& other) const {
    return Vector3{y() * other.z() - z() * other.y(),
                   z() * other.x() - x() * other.z(),
                   x() * other.y() - y() * other.x()};
  }

  static Vector3 Up() { return {0, 1, 0}; }

  static Vector3 Down() { return {0, -1, 0}; }

  static Vector3 Right() { return {1, 0, 0}; }

  static Vector3 Left() { return {-1, 0, 0}; }

  static Vector3 Forward() { return {0, 0, 1}; }

  static Vector3 Backward() { return {0, 0, -1}; }
};

class Vector4 : public Vector<4, Vector4> {};

}  // namespace pjmath
