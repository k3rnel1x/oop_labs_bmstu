#pragma once
#include <vector>
#include <renderer/abstract/ISceneObject.h>
#include "TransformMatrix.h"
#include "Edge.h"
#include "Vertex.h"

class Figure : public ISceneObject {
public:

class FigureMetaInfo {
public:
    double xMax, xMin;
    double yMax, yMin;
    double zMax, zMin;
};

    Figure(std::vector<Vertex>&& vertices, std::vector<Edge>&& edges);

    std::vector<Vertex> GetVertices() const;
    std::vector<Edge>   GetEdges() const;
    void SetVertices(const std::vector<Vertex>& vertices);
    void SetEdges(const std::vector<Edge>& edges);
    FigureMetaInfo GetMetaInfo() const;
    void Transform(const TransformMatrix& transformMatrix);

private:
    std::vector<Vertex> _vertices;
    std::vector<Edge>   _edges;

    FigureMetaInfo _metaInfo;
    void _calculateMetaInfo(const std::vector<Vertex>& vertices);
};
