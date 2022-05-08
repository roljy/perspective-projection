// matrix.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "matrix.h"


/*--------------------------------CONSTRUCTORS--------------------------------*/


Matrix::Matrix()
{
    numOfRows = 0;
    numOfCols = 0;
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
    if (row >= numOfRows || col >= numOfCols) return 0;

    return elements[row][col];
}


std::vector<double> Matrix::getRow(size_t row)
{
    if (row >= numOfRows) return std::vector<double>(numOfCols, 0);

    return elements[row];
}


std::vector<double> Matrix::getCol(size_t col)
{
    if (col >= numOfCols) return std::vector<double>(numOfRows, 0);

    std::vector<double> ans(numOfRows, 0);

    for (size_t i = 0; i < numOfRows; i++)
        ans[i] = elements[i][col];

    return ans;
}


Matrix Matrix::getSubset(size_t rowStart, size_t colStart,
    size_t rowEnd, size_t colEnd)
{
    if (rowEnd < rowStart || colEnd < colStart ||
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


void Matrix::print(unsigned int precision)
{
    std::vector<double> maxVals = max();
    std::vector<double> minVals = min();
    double maxVal = *std::max_element(maxVals.begin(), maxVals.end());
    double minVal = *std::min_element(minVals.begin(), minVals.end());
    if (minVal < 0)
    {
        if ( (maxVal < 0) || ((minVal < 0 ? -minVal : minVal) * 10 > maxVal) )
            maxVal = minVal;
    }

    double absMax = maxVal < 0 ? -maxVal : maxVal;
    unsigned int width = 1;
    while (absMax >= 10)
    {
        absMax /= 10;
        width++;  // each place value greater than ones
    }
    if (maxVal < 0) width++;  // negative sign
    width += precision + (precision ? 1 : 0);  // decimal point and after

    for (size_t i = 0; i < numOfRows; i++)
    {
        for (size_t j = 0; j < numOfCols; j++)
            printf(" %*.*f ", width, precision, elements[i][j]);
        std::cout << std::endl;
    }
}


size_t Matrix::getNumOfRows() { return numOfRows; }


size_t Matrix::getNumOfCols() { return numOfCols; }


double Matrix::determinant()
{
    if (numOfRows != numOfCols) return 0;
    
    switch (numOfRows)
    {
    case 0:
        return 0;
    case 1:
        return elements[0][0];
    case 2:
        return elements[0][0]*elements[1][1] - elements[0][1]*elements[1][0];
    default:
        double ans = 0;
        for (size_t j = 0; j < numOfCols; j++)
        {
            Matrix leftRemaining = getSubset(1, 0, numOfRows, j);
            Matrix rightRemaining = getSubset(1, j+1, numOfRows, numOfCols);
            Matrix remaining = leftRemaining << rightRemaining;
            double currentVal = elements[0][j];
            ans += (j%2 ? -currentVal : currentVal) * remaining.determinant();
        }
        return ans;
    }
}


Matrix Matrix::transpose()
{
    Matrix ans(numOfCols, numOfRows);
    for (size_t j = 0; j < numOfRows; j++)
        ans.setCol(j, elements[j]);
    return ans;
}


Matrix Matrix::absolute()
{
    Matrix ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j,
                elements[i][j] < 0 ? -elements[i][j] : elements[i][j]);
    return ans;
}


/*------------------------------LOGICAL FUNCTIONS-----------------------------*/


bool Matrix::any()
{
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            if (elements[i][j]) return true;

    return false;
}


bool Matrix::all()
{
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            if (!elements[i][j]) return false;

    return true;
}


/*-----------------------------COLUMNWISE FUNCTIONS---------------------------*/


std::vector<double> Matrix::min(int colwise)
{
    std::vector<double> ans = colwise ? getRow(0) : getCol(0);
    
    if (colwise)
        for (size_t j = 0; j < numOfCols; j++)
            for (size_t i = 0; i < numOfRows; i++)
                ans[j] = elements[i][j] < ans[j] ? elements[i][j] : ans[j];
    else
        for (size_t i = 0; i < numOfRows; i++)
            for (size_t j = 0; j < numOfCols; j++)
                ans[i] = elements[i][j] < ans[i] ? elements[i][j] : ans[i];

    return ans;
}


std::vector<double> Matrix::max(int colwise)
{
    std::vector<double> ans = colwise ? getRow(0) : getCol(0);
    
    if (colwise)
        for (size_t j = 0; j < numOfCols; j++)
            for (size_t i = 0; i < numOfRows; i++)
                ans[j] = elements[i][j] > ans[j] ? elements[i][j] : ans[j];
    else
        for (size_t i = 0; i < numOfRows; i++)
            for (size_t j = 0; j < numOfCols; j++)
                ans[i] = elements[i][j] > ans[i] ? elements[i][j] : ans[i];

    return ans;
}


std::vector<double> Matrix::sum(int colwise)
{
    std::vector<double> ans( colwise ? numOfCols : numOfRows, 0 );
    
    if (colwise)
        for (size_t j = 0; j < numOfCols; j++)
            for (size_t i = 0; i < numOfRows; i++)
                ans[j] += elements[i][j];
    else
        for (size_t i = 0; i < numOfRows; i++)
            for (size_t j = 0; j < numOfCols; j++)
                ans[i] += elements[i][j];

    return ans;
}


std::vector<double> Matrix::prod(int colwise)
{
    std::vector<double> ans( colwise ? numOfCols : numOfRows, 1 );
    
    if (colwise)
        for (size_t j = 0; j < numOfCols; j++)
            for (size_t i = 0; i < numOfRows; i++)
                ans[j] *= elements[i][j];
    else
        for (size_t i = 0; i < numOfRows; i++)
            for (size_t j = 0; j < numOfCols; j++)
                ans[i] *= elements[i][j];

    return ans;
}


/*-------------------------------UNARY OPERATORS------------------------------*/


Matrix Matrix::operator+()
{
    return *this;
}


Matrix Matrix::operator-()
{
    Matrix ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, -elements[i][j]);
    return ans;
}


Matrix Matrix::operator!()
{
    Matrix ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, !elements[i][j]);
    return ans;
}


/*-------------------------BINARY ARITHMETIC OPERATORS-----------------------*/


Matrix Matrix::operator+(Matrix &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] + other.getElement(i, j));
    return ans;
}


Matrix Matrix::operator-(Matrix &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] - other.getElement(i, j));
    return ans;
}


Matrix Matrix::operator*(Matrix &other)
{
    // elementwise multiplication
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] * other.getElement(i, j));
    return ans;
}


Matrix Matrix::operator*(double scalar)
{
    Matrix ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] * scalar);
    return ans;
}


Matrix Matrix::operator/(Matrix &other)
{
    // elementwise division
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
        {
            if (!other.getElement(i, j)) return *this;  // division by 0

            ans.setElement(i, j, elements[i][j] / other.getElement(i, j));
        }
    return ans;
}


Matrix Matrix::operator/(double scalar)
{
    if (!scalar) return *this;  // division by 0

    Matrix ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] / scalar);
    return ans;
}


Matrix Matrix::operator->*(Matrix &other)
{
    // matrix multiplication
    if (numOfCols != other.getNumOfRows())
        return *this;

    Matrix ans(numOfRows, other.getNumOfCols());
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < other.getNumOfCols(); j++)
        {
            std::vector<double> row = elements[i];
            std::vector<double> col = other.getCol(j);
            ans.setElement(i, j,
                std::inner_product(row.begin(), row.end(), col.begin(), 0));
        }
    return ans;
}


/*---------------------------BINARY LOGICAL OPERATORS-------------------------*/


Matrix Matrix::operator==(Matrix &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] == other.getElement(i, j));
    return ans;
}


Matrix Matrix::operator!=(Matrix &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] != other.getElement(i, j));
    return ans;
}


Matrix Matrix::operator<(Matrix &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] < other.getElement(i, j));
    return ans;
}


Matrix Matrix::operator<=(Matrix &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] <= other.getElement(i, j));
    return ans;
}


Matrix Matrix::operator>(Matrix &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] > other.getElement(i, j));
    return ans;
}


Matrix Matrix::operator>=(Matrix &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] >= other.getElement(i, j));
    return ans;
}


Matrix Matrix::operator&&(Matrix &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] && other.getElement(i, j));
    return ans;
}


Matrix Matrix::operator||(Matrix &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] || other.getElement(i, j));
    return ans;
}


/*----------------------------OTHER BINARY OPERATORS--------------------------*/


Matrix Matrix::operator<<(Matrix &other)
{
    // right concatenation
    if (numOfRows != other.getNumOfRows()) return *this;

    Matrix ans(numOfRows, numOfCols + other.getNumOfCols());
    ans.setSubset(0, 0, *this);
    ans.setSubset(0, numOfCols, other);
    return ans;
}


Matrix Matrix::operator>>(Matrix &other)
{
    // bottom concatenation
    if (numOfCols != other.getNumOfCols()) return *this;

    Matrix ans(numOfRows + other.getNumOfRows(), numOfCols);
    ans.setSubset(0, 0, *this);
    ans.setSubset(numOfRows, 0, other);
    return ans;
}
