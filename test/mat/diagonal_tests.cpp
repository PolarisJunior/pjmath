#include <pjmath/mat.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include <vector>

#include <utility>

using namespace pjmath;

template <typename Element, std::size_t M, std::size_t N>
void testDiagonalMatrixCase(const std::vector<Element> &values)
{
  std::cerr << "Testing " << M << " by "
            << N << " diagonal matrix" << std::endl;
  for (Element v : values)
  {
    auto mat = Mat<Element, M, N>::diagonal(v);
    EXPECT_FLOAT_EQ(mat.sum(), mat.min_side * v);
    for (std::size_t row = 0; row < M; row++)
    {
      for (std::size_t column = 0; column < N; column++)
      {
        if (row == column)
        {
          EXPECT_FLOAT_EQ(mat.at(row, column), v);
        }
        else
        {
          EXPECT_FLOAT_EQ(mat.at(row, column), 0);
        }
      }
    }
  }
}

template <typename Element, std::size_t M, std::size_t... N>
void testDiagonalMatricesMRows(const std::vector<Element> &values)
{
  ((testDiagonalMatrixCase<Element, M, N>(values)), ...);
}

template <typename Element, std::size_t... M, std::size_t... N>
void testDiagonalMatrices(std::integer_sequence<std::size_t, M...>, std::integer_sequence<std::size_t, N...>, const std::vector<Element> &values)
{
  ((testDiagonalMatricesMRows<Element, M, N...>(values)), ...);
}

TEST(PJ_MAT_TEST, test_diagonal_matrices)
{
  std::integer_sequence<std::size_t, 1, 3, 4, 6, 10, 15, 18> matrix_sizes;
  std::vector<double> dbl_values{-111.1111, -50.0, -23.001, -0.00145, -0.0, 0.0, 0.00123, 12.333, 45.5121};
  std::vector<float> float_values{-111.1111, -50.0, -23.001, -0.00145, -0.0, 0.0, 0.00123, 12.333, 45.5121};
  testDiagonalMatrices<double>(matrix_sizes, matrix_sizes, dbl_values);
  testDiagonalMatrices<float>(matrix_sizes, matrix_sizes, float_values);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
