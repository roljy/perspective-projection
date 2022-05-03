// matrix.cpp

#include <iostream>
#include "matrix.h"


/*--------------------------------CONSTRUCTORS--------------------------------*/


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


/*-----------------------------------GETTERS----------------------------------*/


double Matrix::getElement(size_t row, size_t col)
{
    return elements[row][col];
}


std::vector<double> Matrix::getRow(size_t row)
{
    return elements[row];
}


std::vector<double> Matrix::getCol(size_t col)
{
    std::vector<double> ans(numOfRows, 0);

    for (size_t i = 0; i < numOfRows; i++)
        ans[i] = elements[i][col];

    return ans;
}


Matrix Matrix::getSubset(size_t rowStart, size_t colStart,
    size_t rowEnd, size_t colEnd)
{
    if (rowEnd <= rowStart || colEnd <= colStart ||
        rowEnd > numOfRows || colEnd > numOfCols)
        return Matrix();
    
    Matrix ans(rowEnd - rowStart, colEnd - colStart);
    
    for (size_t i = 0; i < rowEnd - rowStart; i++)
        for (size_t j = 0; j < colEnd - colStart; j++)
            ans.setElement(i, j, elements[rowStart + i][colStart + j]);

    return ans;
}


/*-----------------------------------SETTERS----------------------------------*/


int Matrix::setElement(size_t row, size_t col, double value)
{
    if (row >= numOfRows || col >= numOfCols) return -1;

    elements[row][col] = value;
    return 0;
}


int Matrix::setRow(size_t row, std::vector<double> &values)
{
    if (row >= numOfRows || values.size() != numOfCols) return -1;

    elements[row] = values;
    return 0;
}


int Matrix::setCol(size_t col, std::vector<double> &values)
{
    if (col >= numOfCols || values.size() != numOfRows) return -1;

    for (size_t i = 0; i < numOfRows; i++)
        elements[i][col] = values[i];
    return 0;
}


int Matrix::setSubset(size_t rowStart, size_t colStart, Matrix &values)
{
    if(rowStart + values.getNumOfRows() > numOfRows ||
        colStart + values.getNumOfCols() > numOfCols) return -1;

    for (size_t i = 0; i < values.getNumOfRows(); i++)
        for (size_t j = 0; j < values.getNumOfCols(); j++)
            elements[rowStart + i][colStart + j] = values.getElement(i, j);
    return 0;
}


/*--------------------------BASIC PROPERTIES/ACTIONS--------------------------*/


void Matrix::print()
{
    for (size_t i = 0; i < numOfRows; i++)
    {
        for (size_t j = 0; j < numOfCols; j++)
            std::cout << elements[i][j] << ' ';
        std::cout << std::endl;
    }
}


size_t Matrix::getNumOfRows() { return numOfRows; }


size_t Matrix::getNumOfCols() { return numOfCols; }
