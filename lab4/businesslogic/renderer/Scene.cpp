#include "Scene.h"

void Scene::TransformFigures(const TransformMatrix& transformMatrix)
{
    for (auto& figure: _figures)
        figure.Transform(transformMatrix);
}

std::vector<Figure> Scene::GetFigures() const
{
    return _figures;
}

void Scene::SetFigures(const std::vector<Figure>& figures)
{
    this->_figures = std::vector(figures);
}
