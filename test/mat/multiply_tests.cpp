
#include <pjmath/mat.hpp>
#include <gtest/gtest.h>

using namespace pjmath;

template <typename E>
void testMultiplySquareMatrices()
{
  Mat<E, 4, 4> lhs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  Mat<E, 4, 4> rhs{17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
  Mat<E, 4, 4> expected{250, 260, 270, 280, 618, 644, 670, 696, 986, 1028, 1070, 1112, 1354, 1412, 1470, 1528};

  EXPECT_EQ(lhs * rhs, expected);

  lhs *= rhs;
  EXPECT_EQ(lhs, expected);
}

TEST(PJ_MAT_TEST, test_multiply_square_matrices)
{
  testMultiplySquareMatrices<int>();
}

TEST(PJ_MAT_TEST, test_multiply_matrices)
{
  Mat<int, 1, 1> lhs{5};
  Mat<int, 1, 1> rhs{6};
  Mat<int, 1, 1> expected{30};
  EXPECT_EQ(lhs * rhs, expected);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}