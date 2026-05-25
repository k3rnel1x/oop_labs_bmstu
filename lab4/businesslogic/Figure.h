#pragma once
#include <vector>

#include "Edge.h"
#include "Vertex.h"

class Figure {
public:
    std::vector<Vertex> GetVertices();
    std::vector<Edge>   GetEdges();
    void Transform(const TransformMatrix& transformMatrix);

private:
    std::vector<Vertex> _vertices;
    std::vector<Edge>   _edges;
};
