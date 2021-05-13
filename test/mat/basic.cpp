
#include <gtest/gtest.h>
#include <pjmath/mat3.hpp>

using namespace pjmath;

TEST(mat_basic, multiply)
{
  Mat3 lhs{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Mat3 rhs{10, 11, 12, 13, 14, 15, 16, 17, 18};

  Mat3 expected{84, 90, 96, 201, 216, 231, 318, 342, 366};
  Mat3 result = lhs * rhs;
  lhs *= rhs;

  EXPECT_EQ(result, expected);
  EXPECT_EQ(lhs, expected);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}