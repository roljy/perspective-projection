#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <vector>


class Matrix
{
public:
    // constructor and destructor
    Matrix(unsigned int rows, unsigned int cols, double value = 0);
    ~Matrix();

    // element getters
    double getElement(unsigned int row, unsigned int col);
    std::vector<double> getRow(unsigned int row);
    std::vector<double> getCol(unsigned int col);
    Matrix getSubset(unsigned int rowStart, unsigned int rowEnd,
        unsigned int colStart, unsigned int colEnd);

    // element setters
    int setElement(unsigned int row, unsigned int col, double value);
    int setRow(unsigned int row, std::vector<double> &values);
    int setCol(unsigned int col, std::vector<double> &values);
    int setSubset(unsigned int rowStart, unsigned int colStart, Matrix &values);

    // basic matrix properties/actions
    unsigned int getNumOfRows();
    unsigned int getNumOfCols();
    double determinant();
    Matrix transpose();
    Matrix copy();

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
    Matrix operator=(Matrix &other);
    Matrix operator<<(Matrix &other);
    Matrix operator/(Matrix &other);

private:
    std::vector< std::vector<double> > elements;
    unsigned int numOfRows;
    unsigned int numOfCols;
};

#endif  // SRC_MATRIX_H_
