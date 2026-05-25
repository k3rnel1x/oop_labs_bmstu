#pragma once
#include "Vertex.h"

class Edge {
private:
    Vertex& _begin;
    Vertex& _end;

public:
    Edge(const Edge& edge) = default;
    Edge(Vertex begin, Vertex end)
    : _begin(begin), _end(end)
    {
    };
    Vertex& GetBegin();
    Vertex& GetEnd();

};
