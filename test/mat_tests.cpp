#include <pjmath/mat.hpp>
#include <gtest/gtest.h>

using namespace pjmath;

TEST(PJ_MAT_TEST, addition)
{
  Mat<int, 1, 1> mat1{5};
  Mat<int, 1, 1> mat2{4};
  mat1 += mat2;
  ASSERT_EQ(mat1.at(0, 0), 9);

  auto mat3 = mat1 + mat2;
  ASSERT_EQ(mat3.at(0), 13);

  auto mat4 = -mat3;
  ASSERT_EQ((mat4.get<0, 0>()), -13);

  ASSERT_EQ((Mat<int, 1, 1>::identity().at(0)), 1);
  ASSERT_EQ((Mat<int, 1, 1>::zero().at(0)), 0);
  ASSERT_EQ(mat1.size(), 1);
  mat1.transposed();
}
/**
 * Tests
 * 
 * Diagonal matrices should not change when transposed 
 * The sum of a filled matrix should be size * value
 */

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}