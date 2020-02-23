#include <gtest/gtest.h>

#include "pjmath/vector.hpp"

using namespace pjmath;

TEST(PJ_MATH_TEST, TEMPLATE_VECTOR_TEST) {
  Vector<5> vec{5, 6, 7, 8, 9};
  EXPECT_EQ(vec[0], 5);
  EXPECT_EQ(vec[1], 6);
  EXPECT_EQ(vec[2], 7);
  EXPECT_EQ(vec[3], 8);
  EXPECT_EQ(vec[4], 9);
}

TEST(PJ_MATH_TEST, VECTOR3_TEST) {
  Vector3 v{1, 2, 3};
  v[0] = 5;
  EXPECT_EQ(v.x, 5);
  EXPECT_EQ(v.y, 2);
  EXPECT_EQ(v.z, 3);

  Vector3 vec1{1, 2, 3};
  Vector3 vec2{2, 1, 0};
  vec1 += vec2;
  std::for_each(vec1.begin(), vec1.end(), [](real_t x) { EXPECT_EQ(x, 3); });

  vec1 -= Vector3{1, 1, 1};
  std::for_each(vec1.begin(), vec1.end(), [](real_t x) { EXPECT_EQ(x, 2); });

  Vector3 vec3 = Vector3{3, 4, 6} + Vector3{7, 6, 4};
  std::for_each(vec3.begin(), vec3.end(), [](real_t x) { EXPECT_EQ(x, 10); });
  Vector3 vec4 = vec3 - Vector3{5, 5, 5};
  std::for_each(vec4.begin(), vec4.end(), [](real_t x) { EXPECT_EQ(x, 5); });
  vec4 *= Vector3{3, 3, 3};
  std::for_each(vec4.begin(), vec4.end(), [](real_t x) { EXPECT_EQ(x, 15); });
  vec4 /= Vector3{2, 2, 2};
  std::for_each(vec4.begin(), vec4.end(), [](real_t x) { EXPECT_EQ(x, 7.5); });

  vec4 *= 4;
  std::for_each(vec4.begin(), vec4.end(), [](real_t x) { EXPECT_EQ(x, 30); });
  vec4 /= .5;
  std::for_each(vec4.begin(), vec4.end(), [](real_t x) { EXPECT_EQ(x, 60); });
  EXPECT_EQ(vec4.Dot(Vector3{2, 2, 2}), 360);

  EXPECT_EQ((Vector3{1, 1, 0}).Norm(), std::sqrtf(2.0));

  Vector3 vec5 = vec4.Normalized();
  std::for_each(vec5.begin(), vec5.end(), [](real_t x) { EXPECT_LE(x, .6); });
  real_t n = vec5.Norm();

  EXPECT_FLOAT_EQ(n, 1);
}

TEST(PJ_MATH_TEST, STATIC_MEMBER_TEST) {
  std::for_each(Vector3::zero.begin(), Vector3::zero.end(),
                [](real_t x) { EXPECT_EQ(x, 0); });

  std::for_each(Vector3::one.begin(), Vector3::one.end(),
                [](real_t x) { EXPECT_EQ(x, 1); });
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
