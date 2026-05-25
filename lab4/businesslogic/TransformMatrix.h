#pragma once
#define MATRIXSIZE 4
#include <initializer_list>
#include <string>
#include "3DPoint.h"

class TransformMatrix {
public:
    TransformMatrix() = default;
    TransformMatrix(std::initializer_list<std::initializer_list<double>> list);
    TransformMatrix operator*(TransformMatrix matrix) const;
    Point3D operator()(const Point3D& point) const;
    void printToStdout() const;
    double Get(int row, int col) const;

private:
    double _matrix[MATRIXSIZE][MATRIXSIZE] = {0};
};
