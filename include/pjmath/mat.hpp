
#pragma once

#include "math_defs.hpp"

#include <array>
#include <type_traits>
#include <initializer_list>

namespace pjmath
{
  /**
   * @brief A templated matrix class
   * 
   * @tparam E Element type of the matrix
   * @tparam M Number of rows in the matrix, must be greater than 0
   * @tparam N Number of columns in the matrix, must be greater than 0
   */
  template <typename E, size_t M, size_t N>
  class Mat : public std::array<E, M * N>
  {
  public:
    using Array = std::array<E, M * N>; ///< Array type which backs the matrix

    using Array::Array; ///< Inherit array constructors (there are currently no array constructors)

    static constexpr bool is_square = M == N; ///< True if the matrix is a square matrix

    /**
     * @brief Constructs a Matrix from a parameter pack
     * 
     * @tparam T element types
     * @param elems Elements of the matrix
     */
    template <typename... T>
    Mat(T... elems) : Array({elems...})
    {
    }

    /**
     * @brief Default constructor, value initializes the elements
     */
    Mat() : Array{}
    {
    }

    /**
     * @brief Element-wise addition
     * 
     * @param rhs Matrix to be added to this
     * @return Mat& A reference to this
     */
    Mat &operator+=(const Mat &rhs)
    {
      for (size_t i = 0; i < this->size(); i++)
      {
        this->at(i) += rhs.at(i);
      }
      return *this;
    }

    /**
     * @brief Element-wise addition
     * 
     * @param rhs Matrix to be added with this
     * @return Mat A matrix which is the sum of this and @a rhs
     */
    Mat operator+(const Mat &rhs) const
    {
      Mat mat = *this;
      mat += rhs;
      return mat;
    }

    /**
     * @brief Element-wise subtraction
     * 
     * @param rhs The minuend
     * @return Mat& A reference to this
     */
    Mat &operator-=(const Mat &rhs)
    {
      for (size_t i = 0; i < this->size(); i++)
      {
        this->at(i) -= rhs.at(i);
      }
      return *this;
    }

    /**
     * @brief Element-wise subtraction
     * 
     * @param rhs The minuend
     * @return Mat A matrix which is the result of this - @a rhs
     */
    Mat operator-(const Mat &rhs) const
    {
      Mat mat = *this;
      mat -= rhs;
      return mat;
    }

    /**
     * @brief Element-wise negation
     * 
     * @return Mat A matrix where all the elements are negated from this
     */
    Mat operator-()
    {
      Mat mat = Mat::zero();
      mat -= *this;
      return mat;
    }

    /**
     * @brief Constructs a matrix where all elements are set to the same value
     * 
     * @tparam value The value to set the elements to
     * @return Mat Matrix where all the elements are @a value
     */
    template <E value>
    static constexpr Mat filled()
    {
      Mat mat;
      for (size_t i = 0; i < mat.size(); i++)
      {
        mat.at(i) = value;
      }
      return mat;
    }

    /**
     * @brief Constructs a matrix where all elements are set to the same value
     * 
     * @param value The value to set the elements to
     * @return Mat Matrix where all the elements are @a value
     */
    static Mat filled(const E &value)
    {
      Mat mat;
      for (size_t i = 0; i < mat.size(); i++)
      {
        mat.at(i) = value;
      }
      return mat;
    }

    /**
     * @brief Constructs a zero matrix
     * 
     * @return Mat a matrix where all elements are zero
     */
    static constexpr Mat zero()
    {
      return Mat::filled<0>();
    }

    /**
     * @brief Constructs a matrix where all elements are one
     * 
     * @return Mat a matrix where all elements are one
     */
    static constexpr Mat one()
    {
      return Mat::filled<1>();
    }

    /**
     * @brief Constructs a scalar diagonal matrix
     * 
     * @tparam value Value to be set along the diagonal
     * @return A square matrix where elements along the diagonal equal @a value and all other elements are zero
     */
    template <E value>
    static constexpr typename std::enable_if<Mat::is_square, Mat>::type diagonal()
    {
      Mat mat = Mat::zero();
      for (size_t i = 0; i < N; i += N + 1)
      {
        mat.at(i) = value;
      }
      return mat;
    }

    /**
     * @brief Constructs a scalar diagonal matrix
     * 
     * @param value Value to be set along the diagonal
     * @return A square matrix where elements along the diagonal equal @a value and all other elements are zero
     */
    static constexpr typename std::enable_if<Mat::is_square, Mat>::type diagonal(const E &value)
    {
      Mat mat = Mat::zero();
      for (size_t i = 0; i < N; i += N + 1)
      {
        mat.at(i) = value;
      }
      return mat;
    }

    /**
     * @brief Constructs an identity matrix
     * 
     * @ref Mat::is_square must be true
     * 
     * @return Mat An identity matrix
     */
    static constexpr Mat identity()
    {
      return Mat::diagonal<1>();
    }
  };
}