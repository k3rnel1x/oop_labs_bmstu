#pragma once

#include "Figure.h"


std::vector<Vertex> Figure::GetVertices()
{
    return this->_vertices;
}

std::vector<Edge> Figure::GetEdges()
{
    return this->_edges;
}

void Figure::Transform(const TransformMatrix& transformMatrix)
{
    for (auto& vertex : this->_vertices)
        vertex.Transform(transformMatrix);
}
