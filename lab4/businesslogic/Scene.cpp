#include "Scene.h"

void Scene::TransformFigures(const TransformMatrix& transformMatrix)
{
    for (auto& figure: _figures)
        figure.Transform(transformMatrix);
}

std::vector<Figure> Scene::GetFigures()
{
    return _figures;
}
