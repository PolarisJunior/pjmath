#include <pjmath/mat.hpp>
#include <gtest/gtest.h>
#include <iostream>

#include <utility>

using namespace pjmath;

template <typename Matrix>
class SquareMatrixTest : public testing::Test, public testing::WithParamInterface<Matrix>
{
};

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
  mat1.transpose();

  Mat<int, 1, 2> mat5;
  mat5 += mat5;
}

template <size_t X>
void transposeDiagonalMatrix()
{
}

TEST(PJ_MAT_TEST, transpose_diagonal_matrix)
{
}

template <typename E, E... V>
class ValueSequence
{
};

template <typename E, size_t M, size_t N, E V>
void testFillMatrixCase()
{
  std::cerr << "Testing fill " << M << " by " << N << " matrix with value " << V << std::endl;

  auto runtime = Mat<E, M, N>::filled(V);
  ASSERT_EQ(runtime.sum(), M * N * V);
}

template <typename E, size_t M, size_t N, E... V>
void testFillMatrix()
{
  std::cerr << "Testing fill " << M << " by " << N << " matrix" << std::endl;
  ((testFillMatrixCase<E, M, N, V>()), ...);
}

template <typename E, std::size_t... I, E... V>
void testFillMatrices(std::integer_sequence<std::size_t, I...>, std::integer_sequence<E, V...>)
{
  ((testFillMatrix<E, I, I, V...>()), ...);
}

template <typename Real, size_t M>
void testFillFloatMatrixCase(const std::vector<Real> &values)
{
  std::cerr << "Float Matrix fill " << M << " by " << M << std::endl;
  for (Real v : values)
  {
    std::cerr << "Testing fill " << M << " by " << M << " matrix with value " << v << std::endl;
    auto mat = Mat<Real, M, M>::filled(v);
    ASSERT_FLOAT_EQ(mat.sum(), v * M * M);
  }
}

template <typename Real, std::size_t... M>
void testFillFloatMatrices(const std::vector<Real> &values)
{
  std::cerr << "Starting float test " << values.size() << std::endl;
  ((testFillFloatMatrixCase<Real, M>(values)), ...);
}

TEST(PJ_MAT_TEST, test_fill_matrix)
{

  std::integer_sequence<std::size_t, 1, 3, 5, 7, 9, 15> matrix_sizes;
  std::integer_sequence<int, -200, -33, 0, 1, 5, 10, 110> int_values;
  std::vector<double> dbl_values{-198.173, -47.13, -13.0, -0.0, 0.0, 0.0001, 1.23, 5.17, 199.99};

  testFillMatrices(matrix_sizes, int_values);
  testFillFloatMatrices<double, 1, 3, 4, 7, 9, 12>(dbl_values);
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