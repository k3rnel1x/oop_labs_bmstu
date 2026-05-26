#pragma once
#include <math/TransformMatrix.h>
#include <vector>
#include <math/Figure.h>

class Scene {
public:
    Scene() = default;
    Scene(std::vector<Figure> figures)
    : _figures(std::vector(figures))
    {
    }

    void TransformFigures(const TransformMatrix& transformMatrix);
    std::vector<Figure> GetFigures() const;
    void SetFigures(const std::vector<Figure>& figures);

private:
    std::vector<Figure> _figures;
};
