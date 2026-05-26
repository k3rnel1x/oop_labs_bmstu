#pragma once
#include "TransformMatrix.h"
#include <vector>
#include "Figure.h"

class Scene {
public:
    Scene() = default;
    Scene(std::vector<Figure> figures)
    : _figures(std::vector(figures))
    {
    }

    void TransformFigures(const TransformMatrix& transformMatrix);
    std::vector<Figure> GetFigures();
    void SetFigures(const std::vector<Figure>& figures);

private:
    int _size;
    std::vector<Figure> _figures;
};
