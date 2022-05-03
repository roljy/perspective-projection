// matrix.cpp

#include <iostream>
#include "matrix.h"


Matrix::Matrix()
{
    numOfRows = 1;
    numOfCols = 1;
    elements = std::vector< std::vector<double> > ( numOfRows,
        std::vector<double> (numOfCols, 0) );
}


Matrix::Matrix(size_t rows, size_t cols, double value)
{
    numOfRows = rows;
    numOfCols = cols;

    elements.resize(rows);
    for (size_t i = 0; i < rows; i++)
    {
        elements[i].resize(cols);
        for (size_t j = 0; j < cols; j++)
            elements[i][j] = value;
    }
}


void Matrix::print()
{
    for (size_t i = 0; i < numOfRows; i++)
    {
        for (size_t j = 0; j < numOfCols; j++)
            std::cout << elements[i][j] << ' ';
        std::cout << std::endl;
    }
}


double Matrix::getElement(size_t row, size_t col)
{
    return elements[row][col];
}


size_t Matrix::getNumOfRows() { return numOfRows; }


std::vector<double> Matrix::getRow(size_t row)
{
    return elements[row];
}


size_t Matrix::getNumOfCols() { return numOfCols; }


std::vector<double> Matrix::getCol(size_t col)
{
    std::vector<double> ans(numOfRows, 0);

    for (size_t i = 0; i < numOfRows; i++)
        ans[i] = elements[i][col];

    return ans;
}
