
#include <gtest/gtest.h>
#include <pjmath/vec3.hpp>
#include <pjmath/mat3.hpp>
#include <pjmath/vec4.hpp>
#include <pjmath/mat4.hpp>

using namespace pjmath;

TEST(vec_basic, multiply_3)
{
  Vec3 vec{1, 2, 3};
  Mat3 mat{4, 5, 6, 7, 8, 9, 10, 11, 12};

  Vec3 expected{32, 50, 68};
  Vec3 result = mat * vec;
  EXPECT_EQ(result, expected);
}

TEST(vec_basic, multiply_4)
{
  Vec4 vec{1, 2, 3, 4};
  Mat4 mat{5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

  Vec4 expected{70, 110, 150, 190};
  Vec4 result = mat * vec;
  EXPECT_EQ(result, expected);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}