//
// Created by k3rnel1x on 23.05.2026.
//

#include "TransformMatrixBuilder.h"
#include <valarray>

TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(double alpha, double beta, double gamma)
{
    TransformMatrix xRotMatrix {
        {1, 0, 0},
        {0, cos(alpha), -sin(alpha)},
        {0, sin(alpha), cos(alpha)}
    };

    TransformMatrix yRotMatrix {
        {cos(beta), 0, sin(beta)},
        {0, 1, 0},
        {-sin(beta), 0, cos(beta)},
    };

    TransformMatrix zRotMatrix{
        {cos(gamma), -sin(gamma), 0},
        {sin(gamma), cos(gamma), 0},
        {0, 0, 1},
    };

    return xRotMatrix * yRotMatrix * zRotMatrix;
}

TransformMatrix TransformMatrixBuilder::CreateMoveMatrix(double x, double y, double z)
{
    return TransformMatrix {
            {1, 0, 0, x},
            {0, 1, 0, y},
            {0, 0, 1, z},
            {0, 0, 0, 1},
        };;
}
