#include "Figure.h"

std::vector<Vertex> Figure::GetVertices()
{
    return this->_vertices;
}

void Figure::SetVertices(const std::vector<Vertex>& vertices)
{
    this->_vertices = vertices;
}

void Figure::SetEdges(const std::vector<Edge>& edges)
{
    this->_edges = std::vector(edges);
}

std::vector<Edge> Figure::GetEdges()
{
    return _edges;
}

void Figure::Transform(const TransformMatrix& transformMatrix)
{
    for (auto& vertex : this->_vertices)
        vertex.Transform(transformMatrix);
}

