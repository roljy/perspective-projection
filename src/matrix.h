// matrix.h

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <vector>


template <class T = double>
class Matrix
{
private:
    std::vector< std::vector<T> > elements;
    size_t rows;
    size_t cols;

public:
    // constructors
    Matrix();
    Matrix(size_t rows, size_t cols, T value = 0);

    // element getters
    T getElement(size_t row, size_t col);
    std::vector<T> getRow(size_t row);
    std::vector<T> getCol(size_t col);
    Matrix<T> getSubset(size_t rowStart, size_t colStart,
        size_t rowEnd, size_t colEnd);

    // element setters
    int setElement(size_t row, size_t col, T value);
    int setRow(size_t row, std::vector<T> &values);
    int setCol(size_t col, std::vector<T> &values);
    int setSubset(size_t rowStart, size_t colStart, Matrix<T> &values);

    // basic matrix properties/actions
    size_t getNumOfRows();
    size_t getNumOfCols();
    T determinant();
    Matrix<T> transpose();
    Matrix<T> absolute();

    // difficult fundamentals
    void print(unsigned int precision = 0);
    template <class U = double> Matrix<U> cast();

    // logical functions
    bool any();
    bool all();

    // helpful column/row info functions
    std::vector<T> min(bool colwise = true);
    std::vector<T> max(bool colwise = true);
    std::vector<T> sum(bool colwise = true);
    std::vector<T> prod(bool colwise = true);

    // unary operator overloading
    Matrix<T> operator+();
    Matrix<T> operator-();
    Matrix<bool> operator!();

    // binary arithmetic operator overloading
    Matrix<T> operator+(Matrix &other);
    Matrix<T> operator-(Matrix &other);
    Matrix<T> operator*(Matrix &other);
    Matrix<T> operator*(T scalar);
    Matrix<T> operator/(Matrix &other);
    Matrix<T> operator/(T scalar);
    Matrix<T> operator->*(Matrix &other);

    // binary logical operator overloading
    Matrix<bool> operator==(Matrix &other);
    Matrix<bool> operator!=(Matrix &other);
    Matrix<bool> operator<(Matrix &other);
    Matrix<bool> operator<=(Matrix &other);
    Matrix<bool> operator>(Matrix &other);
    Matrix<bool> operator>=(Matrix &other);
    Matrix<bool> operator&&(Matrix &other);
    Matrix<bool> operator||(Matrix &other);

    // other binary operator overloading
    Matrix<T> operator<<(Matrix &other);
    Matrix<T> operator>>(Matrix &other);
};

#include "matrix.cc"

#endif  // SRC_MATRIX_H_
