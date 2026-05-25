#pragma once
#include "TransformMatrix.h"
#include <vector>
#include "Figure.h"

class Scene {
public:
    void TransformFigures(const TransformMatrix& transformMatrix);
    std::vector<Figure> GetFigures();

private:
    std::vector<Figure> _figures;
};
