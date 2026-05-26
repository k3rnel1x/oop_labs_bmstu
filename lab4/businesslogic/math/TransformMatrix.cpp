//
// Created by k3rnel1x on 23.05.2026.
//

#include "TransformMatrix.h"

#include <initializer_list>
#include <iostream>
#include <ostream>
#include <stdexcept>

TransformMatrix::TransformMatrix(std::initializer_list<std::initializer_list<double>> list)
{
    if (!list.size())
        throw std::invalid_argument("list is empty");

    int r = 0;
    for (const auto& row : list)
    {
        int c = 0;
        for (const double& value : row)
        {
            this->_matrix[r][c++] = value;
        }
        ++r;
    }
}

TransformMatrix TransformMatrix::operator*(TransformMatrix matrix) const
{
    TransformMatrix result{};

    for (int r = 0; r < MATRIXSIZE; ++r) // rows
    {
        for (int c = 0; c < MATRIXSIZE; ++c) // cols
        {
            for (int j = 0; j < MATRIXSIZE; ++j) // elem
            {
                result._matrix[r][j] += this->_matrix[r][c] * matrix._matrix[c][j];
                // std::cout << "result = >" << result._matrix[r][c] << "< " << this->_matrix[r][j] << "*" << matrix._matrix[j][c] << " ";
            }
            // std::cout << std::endl;
        }
    }

    return result;
}

Point3D TransformMatrix::operator()(const Point3D& point) const
{
    Point3D resultPoint = {0};
    TransformMatrix matrix {
        {point.x},
        {point.y},
        {point.z},
        {1}
    };

    // matrix.printToStdout();

    TransformMatrix res = (*this) * matrix;
    // std::cout << "res" << std::endl;
    // res.printToStdout();
    resultPoint.x = res.Get(0, 0);
    resultPoint.y = res.Get(1, 0);
    resultPoint.z = res.Get(2, 0);

    return resultPoint;
}

void TransformMatrix::printToStdout() const
{
    for (int r = 0; r < MATRIXSIZE; ++r)
    {
        for (int c = 0; c < MATRIXSIZE; ++c)
        {
            std::cout << this->_matrix[r][c] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double TransformMatrix::Get(int row, int col) const
{
    if (row < 0 || row >= MATRIXSIZE || col < 0 || col >= MATRIXSIZE)
        throw std::out_of_range("row or column out of range");

    return this->_matrix[row][col];
}

// 1   8 1 4
// 5   2 3 3
// 6   4 5 6