#pragma once
#include <vector>

#include "Edge.h"
#include "Vertex.h"

class Figure {
public:
    Figure(std::vector<Vertex> vertices, std::vector<Edge> edges)
    : _vertices(vertices), _edges(edges)
    {
    }

    std::vector<Vertex> GetVertices();
    std::vector<Edge>   GetEdges();
    void SetVertices(const std::vector<Vertex>& vertices);
    void SetEdges(const std::vector<Edge>& edges);
    void Transform(const TransformMatrix& transformMatrix);

private:
    std::vector<Vertex> _vertices;
    std::vector<Edge>   _edges;
};
