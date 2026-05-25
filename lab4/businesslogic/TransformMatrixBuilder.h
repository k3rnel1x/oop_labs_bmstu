#pragma once
#include <initializer_list>

#include "TransformMatrix.h"

class TransformMatrixBuilder {
public:
    explicit TransformMatrixBuilder(std::initializer_list<std::initializer_list<double>> list);
    static TransformMatrix CreateRotationMatrix(double alpha, double beta, double gamma);
    static TransformMatrix CreateMoveMatrix(double x, double y, double z);
    static TransformMatrix CreateScaleMatrix(double a, double b, double c);
};
