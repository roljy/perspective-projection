// matrix.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "matrix.h"


/*--------------------------------CONSTRUCTORS--------------------------------*/


template <class T>
Matrix<T>::Matrix()
{
    numOfRows = 0;
    numOfCols = 0;
    elements = std::vector< std::vector<T> > ( numOfRows,
        std::vector<T> (numOfCols, 0) );
}


template <class T>
Matrix<T>::Matrix(size_t rows, size_t cols, T value)
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


template <class T>
T Matrix<T>::getElement(size_t row, size_t col)
{
    if (row >= numOfRows || col >= numOfCols) return 0;

    return elements[row][col];
}


template <class T>
std::vector<T> Matrix<T>::getRow(size_t row)
{
    if (row >= numOfRows) return std::vector<T>(numOfCols, 0);

    return elements[row];
}


template <class T>
std::vector<T> Matrix<T>::getCol(size_t col)
{
    if (col >= numOfCols) return std::vector<T>(numOfRows, 0);

    std::vector<T> ans(numOfRows, 0);

    for (size_t i = 0; i < numOfRows; i++)
        ans[i] = elements[i][col];

    return ans;
}


template <class T>
Matrix<T> Matrix<T>::getSubset(size_t rowStart, size_t colStart,
    size_t rowEnd, size_t colEnd)
{
    if (rowEnd < rowStart || colEnd < colStart ||
        rowEnd > numOfRows || colEnd > numOfCols)
        return Matrix<T>();
    
    Matrix<T> ans(rowEnd - rowStart, colEnd - colStart);
    
    for (size_t i = 0; i < rowEnd - rowStart; i++)
        for (size_t j = 0; j < colEnd - colStart; j++)
            ans.setElement(i, j, elements[rowStart + i][colStart + j]);

    return ans;
}


/*-----------------------------------SETTERS----------------------------------*/


template <class T>
int Matrix<T>::setElement(size_t row, size_t col, T value)
{
    if (row >= numOfRows || col >= numOfCols) return -1;

    elements[row][col] = value;
    return 0;
}


template <class T>
int Matrix<T>::setRow(size_t row, std::vector<T> &values)
{
    if (row >= numOfRows || values.size() != numOfCols) return -1;

    elements[row] = values;
    return 0;
}


template <class T>
int Matrix<T>::setCol(size_t col, std::vector<T> &values)
{
    if (col >= numOfCols || values.size() != numOfRows) return -1;

    for (size_t i = 0; i < numOfRows; i++)
        elements[i][col] = values[i];
    return 0;
}


template <class T>
int Matrix<T>::setSubset(size_t rowStart, size_t colStart, Matrix<T> &values)
{
    if(rowStart + values.getNumOfRows() > numOfRows ||
        colStart + values.getNumOfCols() > numOfCols) return -1;

    for (size_t i = 0; i < values.getNumOfRows(); i++)
        for (size_t j = 0; j < values.getNumOfCols(); j++)
            elements[rowStart + i][colStart + j] = values.getElement(i, j);
    return 0;
}


/*--------------------------BASIC PROPERTIES/ACTIONS--------------------------*/


template <class T>
void Matrix<T>::print(unsigned int precision)
{
    std::vector<T> maxVals = max();
    std::vector<T> minVals = min();
    T maxVal = *std::max_element(maxVals.begin(), maxVals.end());
    T minVal = *std::min_element(minVals.begin(), minVals.end());
    if (minVal < 0)
    {
        if ( (maxVal < 0) || ((minVal < 0 ? -minVal : minVal) * 10 > maxVal) )
            maxVal = minVal;
    }

    T absMax = maxVal < 0 ? -maxVal : maxVal;
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


template <class T>
size_t Matrix<T>::getNumOfRows() { return numOfRows; }


template <class T>
size_t Matrix<T>::getNumOfCols() { return numOfCols; }


template <class T>
T Matrix<T>::determinant()
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
        T ans = 0;
        for (size_t j = 0; j < numOfCols; j++)
        {
            Matrix<T> leftRemaining = getSubset(1, 0, numOfRows, j);
            Matrix<T> rightRemaining = getSubset(1, j+1, numOfRows, numOfCols);
            Matrix<T> remaining = leftRemaining << rightRemaining;
            T currentVal = elements[0][j];
            ans += (j%2 ? -currentVal : currentVal) * remaining.determinant();
        }
        return ans;
    }
}


template <class T>
Matrix<T> Matrix<T>::transpose()
{
    Matrix<T> ans(numOfCols, numOfRows);
    for (size_t j = 0; j < numOfRows; j++)
        ans.setCol(j, elements[j]);
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::absolute()
{
    Matrix<T> ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j,
                elements[i][j] < 0 ? -elements[i][j] : elements[i][j]);
    return ans;
}


/*------------------------------LOGICAL FUNCTIONS-----------------------------*/


template <class T>
bool Matrix<T>::any()
{
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            if (elements[i][j]) return true;

    return false;
}


template <class T>
bool Matrix<T>::all()
{
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            if (!elements[i][j]) return false;

    return true;
}


/*-----------------------------COLUMNWISE FUNCTIONS---------------------------*/


template <class T>
std::vector<T> Matrix<T>::min(int colwise)
{
    std::vector<T> ans = colwise ? getRow(0) : getCol(0);
    
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


template <class T>
std::vector<T> Matrix<T>::max(int colwise)
{
    std::vector<T> ans = colwise ? getRow(0) : getCol(0);
    
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


template <class T>
std::vector<T> Matrix<T>::sum(int colwise)
{
    std::vector<T> ans( colwise ? numOfCols : numOfRows, 0 );
    
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


template <class T>
std::vector<T> Matrix<T>::prod(int colwise)
{
    std::vector<T> ans( colwise ? numOfCols : numOfRows, 1 );
    
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


template <class T>
Matrix<T> Matrix<T>::operator+()
{
    return *this;
}


template <class T>
Matrix<T> Matrix<T>::operator-()
{
    Matrix<T> ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, -elements[i][j]);
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator!()
{
    Matrix<T> ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, !elements[i][j]);
    return ans;
}


/*-------------------------BINARY ARITHMETIC OPERATORS-----------------------*/


template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T> &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] + other.getElement(i, j));
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] - other.getElement(i, j));
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> &other)
{
    // elementwise multiplication
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] * other.getElement(i, j));
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator*(T scalar)
{
    Matrix<T> ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] * scalar);
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator/(Matrix<T> &other)
{
    // elementwise division
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
        {
            if (!other.getElement(i, j)) return *this;  // division by 0

            ans.setElement(i, j, elements[i][j] / other.getElement(i, j));
        }
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator/(T scalar)
{
    if (!scalar) return *this;  // division by 0

    Matrix<T> ans = *this;
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] / scalar);
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator->*(Matrix<T> &other)
{
    // matrix multiplication
    if (numOfCols != other.getNumOfRows())
        return *this;

    Matrix<T> ans(numOfRows, other.getNumOfCols());
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < other.getNumOfCols(); j++)
        {
            std::vector<T> row = elements[i];
            std::vector<T> col = other.getCol(j);
            ans.setElement(i, j,
                std::inner_product(row.begin(), row.end(), col.begin(), 0));
        }
    return ans;
}


/*---------------------------BINARY LOGICAL OPERATORS-------------------------*/


template <class T>
Matrix<T> Matrix<T>::operator==(Matrix<T> &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] == other.getElement(i, j));
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator!=(Matrix<T> &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] != other.getElement(i, j));
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator<(Matrix<T> &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] < other.getElement(i, j));
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator<=(Matrix<T> &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] <= other.getElement(i, j));
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator>(Matrix<T> &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] > other.getElement(i, j));
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator>=(Matrix<T> &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] >= other.getElement(i, j));
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator&&(Matrix<T> &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] && other.getElement(i, j));
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator||(Matrix<T> &other)
{
    if (numOfRows != other.getNumOfRows() || numOfCols != other.getNumOfCols())
        return *this;

    Matrix<T> ans(numOfRows, numOfCols);
    for (size_t i = 0; i < numOfRows; i++)
        for (size_t j = 0; j < numOfCols; j++)
            ans.setElement(i, j, elements[i][j] || other.getElement(i, j));
    return ans;
}


/*----------------------------OTHER BINARY OPERATORS--------------------------*/


template <class T>
Matrix<T> Matrix<T>::operator<<(Matrix<T> &other)
{
    // right concatenation
    if (numOfRows != other.getNumOfRows()) return *this;

    Matrix<T> ans(numOfRows, numOfCols + other.getNumOfCols());
    ans.setSubset(0, 0, *this);
    ans.setSubset(0, numOfCols, other);
    return ans;
}


template <class T>
Matrix<T> Matrix<T>::operator>>(Matrix<T> &other)
{
    // bottom concatenation
    if (numOfCols != other.getNumOfCols()) return *this;

    Matrix<T> ans(numOfRows + other.getNumOfRows(), numOfCols);
    ans.setSubset(0, 0, *this);
    ans.setSubset(numOfRows, 0, other);
    return ans;
}
