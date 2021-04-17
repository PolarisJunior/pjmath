#include <pjmath/mat.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include <utility>
#include <vector>

using namespace pjmath;

template <typename E, std::size_t M, std::size_t N>
void testNegateMatrixCase(E value)
{
  auto mat = -Mat<E, M, N>::filled(value);
  EXPECT_FLOAT_EQ(mat.sum(), -value * mat.size());
}

template <typename E, std::size_t M, std::size_t... N>
void testNegateMatricesMRows(const std::vector<E> &values)
{
  ((std::cerr << "Test negate " << M << " by " << N << " matrix" << std::endl), ...);
  for (E v : values)
  {
    ((testNegateMatrixCase<E, M, N>(v)), ...);
  }
}

template <typename E, std::size_t... M, std::size_t... N>
void testNegateMatrices(std::integer_sequence<std::size_t, M...>, std::integer_sequence<std::size_t, N...>, const std::vector<E> &values)
{
  ((testNegateMatricesMRows<E, M, N...>(values)), ...);
}

TEST(PJ_MAT_TEST, test_negate_matrices)
{
  std::integer_sequence<std::size_t, 1, 2, 3, 5, 7, 10> matrix_sizes;
  std::vector<double> dbl_values{-111.1111, -50.0, -23.001, -0.00145, -0.0, 0.0, 0.00123, 12.333, 45.5121};
  testNegateMatrices(matrix_sizes, matrix_sizes, dbl_values);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}