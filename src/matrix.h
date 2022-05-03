#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <vector>


class Matrix
{
public:
    // constructors
    Matrix();
    Matrix(size_t rows, size_t cols, double value = 0);

    // element getters
    double getElement(size_t row, size_t col);
    std::vector<double> getRow(size_t row);
    std::vector<double> getCol(size_t col);
    Matrix getSubset(size_t rowStart, size_t colStart,
        size_t rowEnd, size_t colEnd);

    // element setters
    int setElement(size_t row, size_t col, double value);
    int setRow(size_t row, std::vector<double> &values);
    int setCol(size_t col, std::vector<double> &values);
    int setSubset(size_t rowStart, size_t colStart, Matrix &values);

    // basic matrix properties/actions
    void print();
    size_t getNumOfRows();
    size_t getNumOfCols();
    double determinant();
    Matrix transpose();

    // logical functions
    bool any();
    bool all();

    // unary operator overloading
    Matrix operator+();
    Matrix operator-();
    Matrix operator!();

    // binary arithmetic operator overloading
    Matrix operator+(Matrix &other);
    Matrix operator-(Matrix &other);
    Matrix operator*(Matrix &other);
    Matrix operator/(Matrix &other);
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

private:
    std::vector< std::vector<double> > elements;
    size_t numOfRows;
    size_t numOfCols;
};

#endif  // SRC_MATRIX_H_
