// matrix.h

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <vector>


template <class T = double>
class Matrix
{
private:
    std::vector< std::vector<T> > elements;
    size_t numOfRows;
    size_t numOfCols;

public:
    // constructors
    Matrix();
    Matrix(size_t rows, size_t cols, T value = 0);

    // element getters
    T getElement(size_t row, size_t col);
    std::vector<T> getRow(size_t row);
    std::vector<T> getCol(size_t col);
    Matrix getSubset(size_t rowStart, size_t colStart,
        size_t rowEnd, size_t colEnd);

    // element setters
    int setElement(size_t row, size_t col, T value);
    int setRow(size_t row, std::vector<T> &values);
    int setCol(size_t col, std::vector<T> &values);
    int setSubset(size_t rowStart, size_t colStart, Matrix &values);

    // basic matrix properties/actions
    void print(unsigned int precision = 0);
    size_t getNumOfRows();
    size_t getNumOfCols();
    T determinant();
    Matrix transpose();
    Matrix absolute();

    // logical functions
    bool any();
    bool all();

    // helpful column/row info functions
    std::vector<T> min(int colwise = true);
    std::vector<T> max(int colwise = true);
    std::vector<T> sum(int colwise = true);
    std::vector<T> prod(int colwise = true);

    // unary operator overloading
    Matrix operator+();
    Matrix operator-();
    Matrix operator!();

    // binary arithmetic operator overloading
    Matrix operator+(Matrix &other);
    Matrix operator-(Matrix &other);
    Matrix operator*(Matrix &other);
    Matrix operator*(T scalar);
    Matrix operator/(Matrix &other);
    Matrix operator/(T scalar);
    Matrix operator->*(Matrix &other);

    // binary logical operator overloading
    Matrix operator==(Matrix &other);
    Matrix operator!=(Matrix &other);
    Matrix operator<(Matrix &other);
    Matrix operator<=(Matrix &other);
    Matrix operator>(Matrix &other);
    Matrix operator>=(Matrix &other);
    Matrix operator&&(Matrix &other);
    Matrix operator||(Matrix &other);

    // other binary operator overloading
    Matrix operator<<(Matrix &other);
    Matrix operator>>(Matrix &other);
};

#endif  // SRC_MATRIX_H_
