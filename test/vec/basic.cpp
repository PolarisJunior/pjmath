
#include <gtest/gtest.h>
#include <pjmath/vec3.hpp>
#include <pjmath/mat3.hpp>

using namespace pjmath;

TEST(vec_basic, multiply)
{
  Vec3 vec{1, 2, 3};
  Mat3 mat{4, 5, 6, 7, 8, 9, 10, 11, 12};

  Vec3 expected{32, 50, 68};
  Vec3 result = mat * vec;
  EXPECT_EQ(result, expected);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}