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
                result._matrix[r][c] += this->_matrix[r][j] * matrix._matrix[j][c];
                // std::cout << result._matrix[r][c] << " " << this->_matrix[r][j] << "*" << matrix._matrix[j][c] << std::endl;
            }
        }
    }

    return result;
}

Point3D TransformMatrix::operator()(const Point3D& point) const
{
    Point3D result{};

    for (int r = 0; r < MATRIXSIZE; ++r) // rows
    {
        for (int i = 0; i < MATRIXSIZE; ++i) // elem
        {
            result.x += point.x * this->_matrix[r][0];
            result.y += point.y * this->_matrix[r][1];
            result.z += point.z * this->_matrix[r][2];
        }
    }

    return result;
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

// 1   8 1 4
// 5   2 3 3
// 6   4 5 6