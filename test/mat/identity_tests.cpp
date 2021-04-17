#include <pjmath/mat.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include <utility>

using namespace pjmath;

template <typename Element, std::size_t M>
void testIdentityMatrixCase()
{
  std::cerr << "Testing " << M << " by "
            << M << " identity matrix" << std::endl;
  auto mat = Mat<Element, M, M>::identity();
  EXPECT_FLOAT_EQ(mat.sum(), M);

  for (std::size_t row = 0; row < M; row++)
  {
    for (std::size_t column = 0; column < M; column++)
    {
      if (row == column)
      {
        EXPECT_FLOAT_EQ(mat.at(row, column), 1);
      }
      else
      {
        EXPECT_FLOAT_EQ(mat.at(row, column), 0);
      }
    }
  }
}

template <typename Element, std::size_t... M>
void testIdentityMatrices(std::integer_sequence<std::size_t, M...>)
{
  ((testIdentityMatrixCase<Element, M>()), ...);
}

TEST(PJ_MAT_TEST, test_identity_matrix)
{
  std::integer_sequence<std::size_t, 1, 3, 5, 7, 9, 11, 20> matrix_sizes;
  testIdentityMatrices<double>(matrix_sizes);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}