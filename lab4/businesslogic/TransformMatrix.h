#pragma once
#define MATRIXSIZE 3
#include <initializer_list>

#include "3DPoint.h"

class TransformMatrix {
public:
    TransformMatrix() = default;
    TransformMatrix(std::initializer_list<std::initializer_list<double>> list);
    TransformMatrix operator*(TransformMatrix matrix) const;
    Point3D operator()(const Point3D& point) const;
    void printToStdout() const;

private:
    double _matrix[MATRIXSIZE][MATRIXSIZE] = {0};

};
