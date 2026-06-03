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
    if (fabs(res.Get(0, 0)) > 40 || fabs(res.Get(1, 0)) > 50 || fabs(res.Get(2, 0)) > 50)
    {
        _point.x -= 0.01;
        _point.y -= 0.01;
        _point.z -= 0.01;
        throw std::runtime_error("Moving outside");
    }
    // {
    _point = Point3D {
        .x = res.Get(0, 0),
        .y = res.Get(1, 0),
        .z = res.Get(2, 0)
    };
    // }


    // if (fabs(p.x) < 50 && fabs(p.y) < 50 && fabs(p.z) < 50)
        // this->_point = std::move(p);
    // {
        // res.printToStdout();
    // }
    // std::cout << "After:" << std::endl;
}