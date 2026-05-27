#include "Figure.h"

#include "io/NormalizationParams.h"

Figure::Figure(std::vector<Vertex>&& vertices, std::vector<Edge>&& edges)
    : _vertices(vertices), _edges(edges)
{
    _calculateMetaInfo();
}

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

Figure::FigureMetaInfo Figure::GetMetaInfo()
{
    return this->_metaInfo;
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

void Figure::_calculateMetaInfo()
{
    if (!_vertices.size())
        return;

    // Fill FigureMetaInfo
    Point3D first = _vertices[0].GetPosition();
    double yMax = first.y, yMin = first.y;
    double xMax = first.x, xMin = first.x;
    double zMax = first.z, zMin = first.z;
    for (const auto& v : _vertices) {
        Point3D p = v.GetPosition();
        if (zMax < p.z) zMax = p.z;
        if (yMax < p.y) yMax = p.y;
        if (xMax < p.x) xMax = p.x;

        if (xMin > p.x) xMin = p.x;
        if (yMin > p.y) yMin = p.y;
        if (zMin > p.z) zMin = p.z;
    }

    _metaInfo = FigureMetaInfo {
        .xMax = xMax + 1, .xMin = xMin,
        .yMax = yMax + 1, .yMin = yMin,
        .zMax = zMax + 1, .zMin = zMin
    };
}

