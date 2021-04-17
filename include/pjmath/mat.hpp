
#pragma once

#include <array>
#include <type_traits>

namespace pjmath
{
  /**
   * @brief A templated matrix class
   * 
   * @tparam E Element type of the matrix
   * @tparam M Number of rows in the matrix, must be greater than 0
   * @tparam N Number of columns in the matrix, must be greater than 0
   * @tparam Derived Concrete class for CRTP
   */
  template <typename E, size_t M, size_t N, typename Derived = void>
  class Mat : public std::array<E, M * N>
  {
  public:
    using Array = std::array<E, M * N>;          ///< Array type which backs the matrix
    using Transpose = Mat<E, N, M>;              ///< Type for a transpose of this matrix type
    using size_type = typename Array::size_type; ///< Array size type

    using Self = typename std::conditional<std::is_void<Derived>::value, Mat, Derived>::type; ///< Self type for CRTP

    using Array::Array; ///< Inherit array constructors (there are currently no array constructors)
    using Array::at;    ///< We provide overloads of `at`, so this must be explicitly inherited

    static constexpr bool is_square = M == N;            ///< True if the matrix is a square matrix
    static constexpr size_type row_count = M;            ///< Number of rows
    static constexpr size_type column_count = N;         ///< Number of columns
    static constexpr size_type min_side = M > N ? N : M; ///< The number of rows or columns depending on which is less
    static constexpr size_type max_side = M > N ? M : N; ///< The  number of rows or columns depending on which is greater

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
     * @brief Gets the element at the given row and column
     * 
     * @param r Row
     * @param c Column
     * @return Const reference to the element
     */
    const E &at(size_type r, size_type c) const
    {
      return this->at(r * N + c);
    }

    /**
     * @brief Gets the element at the given row and column
     * 
     * @param r Row
     * @param c Column
     * @return Reference to the element
     */
    E &at(size_type r, size_type c)
    {
      return this->at(r * N + c);
    }

    /**
     * @brief Gets the element at the given row and column
     * 
     * @tparam r Row
     * @tparam c Column
     * @return Const reference to the element
     */
    template <size_type r, size_type c>
    const E &get() const
    {
      return std::get<r * N + c>(*this);
    }

    /**
     * @brief Gets the element at the given row and column
     * 
     * @tparam r Row
     * @tparam c Column
     * @return Reference to the element
     */
    template <size_type r, size_type c>
    E &get()
    {
      return std::get<r * N + c>(*this);
    }

    /**
     * @brief Element-wise addition
     * 
     * @param rhs Matrix to be added to this
     * @return A reference to this
     */
    Self &operator+=(const Mat &rhs)
    {
      for (size_type i = 0; i < this->size(); i++)
      {
        this->at(i) += rhs.at(i);
      }
      return *self();
    }

    /**
     * @brief Element-wise addition
     * 
     * @param rhs Matrix to be added with this
     * @return A matrix which is the sum of this and @a rhs
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
     * @return A reference to this
     */
    Self &operator-=(const Mat &rhs)
    {
      for (size_type i = 0; i < this->size(); i++)
      {
        this->at(i) -= rhs.at(i);
      }
      return *self();
    }

    /**
     * @brief Element-wise subtraction
     * 
     * @param rhs The minuend
     * @return A matrix which is the result of this - @a rhs
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
     * @return A matrix where all the elements are negated from this
     */
    Mat operator-() const
    {
      Mat mat = Mat::zero();
      mat -= *this;
      return mat;
    }

    /**
     * @brief Element-wise multiplication by a scalar
     * 
     * @param v Multiplication factor
     * @return Reference to this
     */
    Self &operator*=(const E &v)
    {
      for (E &e : *this)
      {
        e *= v;
      }
      return *self();
    }

    /**
     * @brief Element-wise multiplication by a scalar
     * 
     * @param v Multiplication factor
     * @return Matrix whose elements are this matrix's elements multiplied by @a v
     */
    Mat operator*(const E &v) const
    {
      Mat mat = *this;
      mat *= v;
      return mat;
    }

    Self &fill(const E &value)
    {
      for (size_type i = 0; i < this->size(); i++)
      {
        this->at(i) = value;
      }
      return *self();
    }

    /**
     * @brief Constructs a matrix where all elements are set to the same value
     * 
     * @param value The value to set the elements to
     * @return Matrix where all the elements are @a value
     */
    static Mat filled(const E &value)
    {
      Mat mat;
      mat.fill(value);
      return mat;
    }

    /**
     * @brief Constructs a zero matrix
     * 
     * @return A matrix where all elements are zero
     */
    static Mat zero()
    {
      return Mat::filled(0);
    }

    /**
     * @brief Constructs a matrix where all elements are one
     * 
     * @return A matrix where all elements are one
     */
    static Mat one()
    {
      return Mat::filled(1);
    }

    /**
     * @brief Constructs a diagonal matrix. 
     * 
     * @param value Value to be set along the diagonal
     * @return A matrix whose elements along the diagonal equal @a value and all other elements are zero
     */
    static Self diagonal(const E &value)
    {
      Self mat = Self::zero();
      for (size_type i = 0; i < mat.min_side; i++)
      {
        mat.at(i, i) = value;
      }
      return mat;
    }

    /**
     * @brief Constructs an identity matrix
     * 
     * @ref Mat::is_square must be true
     * 
     * @return An identity matrix
     */
    static Mat identity()
    {
      return Mat::diagonal(1);
    }

    /**
     * @brief Returns the transpose of this matrix
     * 
     * @return A new matrix which is the transpose of this matrix 
     */
    Transpose transposed() const
    {
      Transpose mat;
      for (size_type row = 0; row < row_count; row++)
      {
        for (size_type column = 0; column < column_count; column++)
        {
          mat.at(column, row) = this->at(row, column);
        }
      }
      return mat;
    }

    /**
     * @brief Transposes the elements of this matrix
     * 
     * @ref Mat::is_square must be true since this performs the transpose in place
     * 
     * @return A reference to this
     */
    template <typename T = Self>
    typename std::enable_if<M == N, T>::type &transpose()
    {
      for (size_type row = 0; row < row_count; row++)
      {
        for (size_type column = 0; column < column_count; column++)
        {
          E temp = this->at(row, column);
          this->at(row, column) = this->at(column, row);
          this->at(column, row) = temp;
        }
      }
      return *this;
    }

    /**
     * @brief Computes the sum of all elements in the matrix
     * 
     * @return The sum of all elements in the matrix
     */
    E sum() const
    {
      E ret{};
      for (const E &value : *this)
      {
        ret += value;
      }
      return ret;
    }

  protected:
    /**
     * @return A this pointer using the derived type 
     */
    Self *self()
    {
      return dynamic_cast<Self *>(this);
    }

    /**
     * @return A const this pointer using the derived type 
     */
    const Self *self() const
    {
      return dynamic_cast<const Self *>(this);
    }
  };

}