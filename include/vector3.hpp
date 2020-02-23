#pragma once

#include <math.h>
#include <sstream>
#include <string>
#include "math_defs.h"

namespace pjmath {

class Vector3 {
 public:
  union {
    struct {
      real_t x;
      real_t y;
      real_t z;
    };

    real_t coord[3];
  };

  Vector3() = default;
  Vector3(real_t x, real_t y, real_t z) noexcept : x(x), y(y), z(z) {}

  Vector3 operator+(const Vector3& other) const noexcept {
    return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
  }
  Vector3 operator-(const Vector3& other) const noexcept {
    return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
  }

  Vector3 operator*(real_t scale) const noexcept {
    return Vector3(this->x * scale, this->y * scale, this->z * scale);
  }
  Vector3 operator*(const Vector3& other) const noexcept {
    return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
  }

  Vector3 operator/(real_t divisor) const noexcept {
    return Vector3(this->x / divisor, this->y / divisor, this->z / divisor);
  }
  Vector3 operator/(const Vector3& other) const noexcept {
    return Vector3(this->x / other.x, this->y / other.y, this->z / other.z);
  }

  Vector3 operator-() const noexcept { return Vector3(-x, -y, -z); }

  Vector3& operator+=(const Vector3& other) noexcept {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
  }

  Vector3& operator-=(const Vector3& other) noexcept {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
  }

  Vector3& operator*=(real_t scale) noexcept {
    this->x *= scale;
    this->y *= scale;
    this->z *= scale;
    return *this;
  }

  Vector3& operator*=(const Vector3& other) noexcept {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
  }

  Vector3& operator/=(real_t divisor) noexcept {
    this->x /= divisor;
    this->y /= divisor;
    this->z /= divisor;
    return *this;
  }

  bool operator==(const Vector3& other) const noexcept {
    return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
  }
  bool operator!=(const Vector3& other) const noexcept {
    return !(*this == other);
  }

  Vector3 Normalized() const {
    Vector3 ret = *this;
    ret.Normalize();
    return ret;
  }

  Vector3& Normalize() {
    if (Length() > 0) {
      *this /= Length();
    }
    return *this;
  }

  real_t Length() const { return static_cast<real_t>(sqrt(Dot(*this))); }

  real_t Magnitude() const { return Length(); }

  bool Equals(const Vector3& other, real_t delta) const {
    return fabs(this->x - other.x) + fabs(this->y - other.y) +
               fabs(this->z - other.z) <
           delta;
  }

  real_t Dot(const Vector3& other) const noexcept {
    return this->x * other.x + this->y * other.y + this->z * other.z;
  }

  Vector3 Cross(const Vector3& other) const noexcept {
    return Vector3(y * other.z - z * other.y, z * other.x - x * other.z,
                   x * other.y - y * other.x);
  }

  real_t Pitch() const noexcept { return this->x; }

  real_t Yaw() const noexcept { return this->y; }

  real_t Roll() const noexcept { return this->z; }

  std::string ToString() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ", " << z << ")";
    return ss.str();
  }

  const static Vector3 zero;
  const static Vector3 one;
  const static Vector3 right;
  const static Vector3 left;
  const static Vector3 up;
  const static Vector3 down;
  const static Vector3 front;
  const static Vector3 back;
  const static Vector3 forward;
  const static Vector3 backward;
};

const Vector3 Vector3::zero = Vector3(0, 0, 0);
const Vector3 Vector3::one = Vector3(1, 1, 1);
const Vector3 Vector3::right = Vector3(1, 0, 0);
const Vector3 Vector3::left = Vector3(-1, 0, 0);
const Vector3 Vector3::up = Vector3(0, 1, 0);
const Vector3 Vector3::down = Vector3(0, -1, 0);
const Vector3 Vector3::forward = Vector3(0, 0, 1);
const Vector3 Vector3::backward = Vector3(0, 0, -1);
}  // namespace pjmath
