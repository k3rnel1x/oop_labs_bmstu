#pragma once
#include "Vertex.h"

class Edge {
private:
    Vertex& _begin;
    Vertex& _end;

public:
    Vertex& GetBegin();
    Vertex& GetEnd();

};
