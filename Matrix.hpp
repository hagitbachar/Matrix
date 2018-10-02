#include <iostream>
#include <vector>
#include "Complex.h"
#include "Exception.h"

#define ZERO 0
#define MIN_SIZE 1

/**
 * class that create matrix and has matrix function
 * @tparam T
 */
template <class T>
class Matrix
{
private:
    std::vector<T> _matrix;
    unsigned int _rows;
    unsigned int _cols;

public:
    /**
     * defult constructor that init a square matrix with size 1, and the single element is zero
     */
    Matrix():_rows(MIN_SIZE), _cols(MIN_SIZE){this->_matrix.resize(MIN_SIZE, T(ZERO)); }

    /**
     * constructor that init a matrix with the given size, and all the matrix's elements is zero
     * @param rows the rows size
     * @param cols the cols size
     */
    Matrix(unsigned int rows, unsigned int cols);

    /**
     * copy constructor
     * @param other the matrix to be copy
     */
    Matrix(const Matrix& other);

    /**
     * move constructor
     * @param other the matrix to be moved
     */
    Matrix(const Matrix && other) ;

    /**
     * constructor that init a matrix with the given size, and the matrix's elements will be the vector's elements
     * @param rows the rows size
     * @param cols the cols size
     * @param cells the vector of the elements
     */
    Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells);

    /**
     * destructor that delete th matrix
     */
    ~Matrix(){this->_matrix.clear(); }

    /**
     * overloading the assignment operator
     * @param matrix2 to assign
     * @return the assign matrix
     */
    Matrix<T>&  operator=(const Matrix<T>& matrix2);

    /**
     * overloading the plus operator
     * @param matrix2 to add
     * @return the added matrix
     */
    Matrix<T>  operator+(const Matrix<T>& matrix2) const;

    /**
     * overloading the subtraction operator
     * @param matrix2 to subtract
     * @return the result
     */
    Matrix<T>  operator-(const Matrix<T>& matrix2) const;

    /**
     * overloading the multiplication operator
     * @param matrix2 to multiple
     * @return the result
     */
    Matrix<T>  operator*(const Matrix<T>& matrix2) const;

    /**
     * overloading the comparison operator
     * @param matrix2 to check comparison
     * @return true if they equal, false otherwise
     */
    bool  operator==(const Matrix<T>& matrix2) const;

    /**
     * overloading the non-comparison operator
     * @param matrix2 to check comparison
     * @return true if they not equal, false otherwise
     */
    bool  operator!=(const Matrix<T>& matrix2) const;

    /**
     * transpose the matrix
     * @return the transpose matrix
     *
     */
    Matrix<T> trans();

    /**
     * check if the the matrix is square
     * @return
     */
    bool isSquareMatrix() const;

    /**
     * overloading the output operator
     * @param os the ostream
     * @param matrix to print
     * @return the ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>&  matrix)
    {
        for (unsigned int i = 0; i < matrix._rows; ++i)
        {
            for (unsigned int j = 0; j < matrix._cols; ++j)
            {
                os << matrix(i, j) << "\t";
            }
            os << std:: endl;
        }
        return os;
    }

    /**
     * overloading the brackets operator, for const matrix
     * @param row the row
     * @param col the col
     * @return the element in the given indexes
     */
    const T& operator()(unsigned int row, unsigned int col) const;

    /**
     * overloading the brackets operator
     * @param row the row
     * @param col the col
     * @return the element in the given indexes
     */
    T& operator()(unsigned int row, unsigned int col);

    typedef typename std::vector<T>::const_iterator iter;

    /**
     * begin iterator
     * @return pointer to the first cell in the vector
     */
    iter begin(){ return this->begin(); }

    /**
     * end iterator
     * @return pointer to the last cell in the vector
     */
    iter end(){ return this->end(); }

    /**
     * getter to the row member
     * @return the row
     */
    int rows(){ return this->_rows; }

    /**
     * getter to the col member
     * @return the col
     */
    int cols(){ return this->_cols; }
};

/**
 * constructor that init a matrix with the given size, and all the matrix's elements is zero
 * @param rows the rows size
 * @param cols the cols size
 */
template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols):_rows(rows), _cols(cols)
{
    //check if the size correct
    if(rows < MIN_SIZE || cols < MIN_SIZE)
    {
        throw IllegalSize();
    }
    try
    {
        _matrix.resize(rows * cols, T(ZERO));
    }
    catch (std::bad_alloc e)
    {
        throw e;
    }

}

/**
 * copy constructor
 * @param other the matrix to be copy
 */
template <class T>
Matrix<T>::Matrix(const Matrix& other):_rows(other._rows), _cols(other._cols)
{
    //check if the size correct
    if(other._rows < MIN_SIZE || other._cols < MIN_SIZE)
    {
        throw IllegalSize();
    }
    try
    {
        this->_matrix = other._matrix;
    }
    catch (std::bad_alloc e)
    {
        throw e;
    }
}

/**
 * move constructor
 * @param other the matrix to be moved
 */
template <class T>
Matrix<T>::Matrix(const Matrix && other):_rows(other._rows), _cols(other._cols)
{
    //check if the size correct
    if(other._rows < MIN_SIZE || other._cols < MIN_SIZE)
    {
        throw IllegalSize();
    }
    try
    {
        this->_matrix = std::move(other._matrix);
    }
    catch (std::bad_alloc e)
    {
        throw e;
    }

}

/**
 * constructor that init a matrix with the given size, and the matrix's elements will be the vector's elements
 * @param rows the rows size
 * @param cols the cols size
 * @param cells the vector of the elements
 */
template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells):_rows(rows), _cols(cols)
{
    //check if the size correct
    if(rows < MIN_SIZE || cols < MIN_SIZE)
    {
        throw IllegalSize();
    }
    else if(cells.size() != rows * cols)
    {
        throw NoMatchNumOfCells();
    }
    try
    {
        this->_matrix.resize(rows * cols, T(ZERO));
        for (unsigned int i = 0; i < rows * cols; ++i)
        {
            this->_matrix[i] = cells[i];
        }
    }
    catch (std::bad_alloc e)
    {
        throw e;
    }
}

/**
 * overloading the assignment operator
 * @param matrix2 to assign
 * @return the result
 */
template <class T>
Matrix<T>&  Matrix<T>::operator=(const Matrix<T>& matrix2) //todo
{
    Matrix<T> newMatrix(matrix2);
    this->_matrix.swap(newMatrix._matrix);
    this->_rows = newMatrix._rows;
    this->_cols = newMatrix._cols;
    return *this;
}

/**
 * overloading the plus operator
 * @param matrix2 to add
 * @return the result
 */
template <class T>
Matrix<T>  Matrix<T>::operator+(const Matrix<T>& matrix2) const
{
    //check correct size
    if(matrix2._rows != this->_rows || matrix2._cols != this->_cols)
    {
        throw DifferentMatricesSize();
    }
    else
    {
        Matrix<T> newMatrix = Matrix(this->_rows, this->_cols);
        for (unsigned int i = 0; i < _rows * _cols; ++i)
        {
            newMatrix._matrix[i] = this->_matrix[i] + matrix2._matrix[i];
        }
        return newMatrix;
    }
}

/**
 * overloading the subtraction operator
 * @param matrix2 to substruct
 * @return the result
 */
template <class T>
Matrix<T>  Matrix<T>::operator-(const Matrix<T>& matrix2) const
{
    //check correct size
    if(matrix2._rows != this->_rows || matrix2._cols != this->_cols)
    {
        throw DifferentMatricesSize();
    }
    else
    {
        Matrix<T> newMatrix = Matrix(this->_rows, this->_cols);
        for (unsigned int i = 0; i < _rows * _cols; ++i)
        {
            newMatrix._matrix[i] = this->_matrix[i] - matrix2._matrix[i];
        }
        return newMatrix;
    }
}

/**
 * overloading the multiplication operator
 * @param matrix2 to multiple
 * @return the result
 */
template <class T>
Matrix<T>  Matrix<T>::operator*(const Matrix<T>& matrix2) const
{
    //to multiple two matrices the first'number of cols need to be equal to the second' number of rows.
    if(this->_cols != matrix2._rows)
    {
        throw DifferentMatricesSize();
    }
    else
    {
        T sumElements;
        Matrix<T> newMatrix = Matrix(this->_rows, matrix2._cols);
        for (unsigned int i = 0; i < this->_rows; ++i)
        {
            for (unsigned int j = 0; j < matrix2._cols; ++j)
            {
                sumElements = T(ZERO);
                for (unsigned int k = 0; k < this->_cols; ++k)
                {
                    sumElements += (*this)(i, k) * matrix2(k, j);

                }
                newMatrix(i, j) = sumElements;
            }
        }
        return newMatrix;
    }
}

/**
 * overloading the comparison operator
 * @param matrix2 to check comparison
 * @return true if they equal, false otherwise
 */
template <class T>
bool  Matrix<T>::operator==(const Matrix<T>& matrix2) const
{
    if(this->_rows != matrix2._rows || this->_cols != matrix2._cols)
    {
        throw DifferentMatricesSize();
    }
    for (unsigned int i = 0; i < this->_rows * this->_cols; ++i)
    {
        if(this->_matrix[i] != matrix2._matrix[i])
        {
            return false;
        }
    }
    return true;
}

/**
 * overloading the non-comparison operator
 * @param matrix2 to check comparison
 * @return true if they not equal, false otherwise
 */
template <class T>
bool  Matrix<T>::operator!=(const Matrix<T>& matrix2) const
{
    return !(*this == matrix2);
}

/**
 * transpose the matrix
 * @return the transpose matrix
 *
 */
template <class T>
Matrix<T> Matrix<T>::trans()
{
    if(! this->isSquareMatrix())
    {
        throw UnsquareMatrix();
    }
    else
    {
        Matrix<T> transposeMatrix = Matrix(this->_rows, this->_rows); //The matrix is square
        for (unsigned int i = 0; i < this->_rows; ++i)
        {
            for (unsigned int j = 0; j < this->_rows; ++j)
            {
                transposeMatrix(j, i) = (*this)(i, j);
            }
        }
        return transposeMatrix;
    }
}

/**
 * transpose the complex matrix
 * @return the transpose matrix
 *
 */
template <>
Matrix<Complex> Matrix<Complex>::trans()
{
    if(! this->isSquareMatrix())
    {
        throw UnsquareMatrix();
    }
    else
    {
        Matrix<Complex> transposeMatrix = Matrix(this->_rows, this->_rows); //The matrix is square
        for (unsigned int i = 0; i < this->_rows; ++i)
        {
            for (unsigned int j = 0; j < this->_rows; ++j)
            {
                transposeMatrix(j, i) = (*this)(i, j);
            }
        }
        return transposeMatrix;
    }
};

/**
 * check if the the matrix is square
 * @return
 */
template <class T>
bool Matrix<T>::isSquareMatrix() const
{
    return this->_cols == this->_rows;
}

/**
 * overloading the brackets operator, for const matrix
 * @param row the row
 * @param col the col
 * @return the element in the given indexes
 */
template <class T>
const T& Matrix<T>::operator()(unsigned int row, unsigned int col) const
{
    if(row > this->_rows || col > this->_cols)
    {
        throw IllegalIndex();
    }
    return this->_matrix[row * this->_cols + col];
}

/**
 * overloading the brackets operator
 * @param row the row
 * @param col the col
 * @return the element in the given indexes
 */
template <class T>
T& Matrix<T>::operator()(unsigned int row, unsigned int col)
{
    if(row > this->_rows || col > this->_cols)
    {
        throw IllegalIndex();
    }
    return this->_matrix[row * this->_cols + col];
}
