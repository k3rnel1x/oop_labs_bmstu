#include "Vertex.h"

#include <iostream>
#include <ostream>
#include <qlogging.h>

Point3D Vertex::GetPosition() const
{
    return this->_point;
}

void Vertex::Transform(const TransformMatrix& transform)
{
    TransformMatrix vertexMatrix  {
        {_point.x},
        {_point.y},
        {_point.z},
        {1}
    };

    // std::cout << "Transform:" << std::endl;
    // transform.printToStdout();

    // std::cout << "Before:" << std::endl;
    // vertexMatrix.printToStdout();
    TransformMatrix res = transform * vertexMatrix;
    _point = Point3D {
        .x = res.Get(0, 0),
        .y = res.Get(1, 0),
        .z = res.Get(2, 0)
    };

    // std::cout << "After:" << std::endl;
    // res.printToStdout();
}