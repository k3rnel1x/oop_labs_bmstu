#pragma once
#include <vector>
#include <renderer/abstract/ISceneObject.h>
#include "TransformMatrix.h"
#include "Edge.h"
#include "Vertex.h"

class Figure : public ISceneObject {
public:
    Figure(std::vector<Vertex>&& vertices, std::vector<Edge>&& edges)
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
