#pragma once
#include "3DPoint.h"
#include "TransformMatrix.h"

class Vertex {
public:
    Vertex() = default;
    Vertex(Point3D point) : _point(point) {}
    Point3D GetPosition() const;
    void Transform(const TransformMatrix& transform);

private:
    Point3D _point = {0,0,0};
};
