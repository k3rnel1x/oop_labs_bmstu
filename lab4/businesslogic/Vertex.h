#pragma once
#include "3DPoint.h"
#include "TransformMatrix.h"

class Vertex {
public:
    Point3D GetPosition() const;
    void Transform(const TransformMatrix& transform);
private:
    Point3D _point;
};
