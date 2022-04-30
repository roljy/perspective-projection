#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <vector>


class Matrix
{
public:
    // constructor and destructor
    Matrix(unsigned int rows, unsigned int cols);
    ~Matrix();

    // access elements
    double getElement(unsigned int row, unsigned int col);
    std::vector<double> getRow(unsigned int row);
    std::vector<double> getCol(unsigned int col);
    Matrix getSubset(unsigned int rowStart, unsigned int rowEnd,
        unsigned int colStart, unsigned int colEnd);

    // basic matrix properties/actions
    unsigned int getNumOfRows();
    unsigned int getNumOfCols();
    double determinant();
    Matrix transpose();
    Matrix inverse();

    // unary operator overloading
    Matrix operator+();
    Matrix operator-();
    Matrix operator!();

    // binary arithmetic operator overloading
    Matrix operator+(Matrix &other);
    Matrix operator-(Matrix &other);
    Matrix operator*(Matrix &other);

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
    Matrix operator=(Matrix &other);
    Matrix operator>>(Matrix &other);
    Matrix operator/(Matrix &other);

private:
    std::vector< std::vector<double> > elements;
    unsigned int numOfRows;
    unsigned int numOfCols;
};

#endif  // SRC_MATRIX_H_
