#pragma once

#include "Vertex.h"

Point3D Vertex::GetPosition() const
{
    return this->_point;
}

void Vertex::Transform(const TransformMatrix& transform)
{
    TransformMatrix vertexMatrix  {
        {_point.x},
        {_point.y},
        {_point.z}
    };

    TransformMatrix res = transform * vertexMatrix;
    _point = Point3D {
        .x = res.Get(0, 0),
        .y = res.Get(1, 0),
        .z = res.Get(2, 0)
    };
}