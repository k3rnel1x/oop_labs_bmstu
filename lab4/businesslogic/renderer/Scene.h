#pragma once
#include <math/TransformMatrix.h>
#include <vector>
#include <math/Figure.h>

#include "io/NormalizationParams.h"

class Scene {
public:
    Scene() = default;
    Scene(std::vector<Figure>&& figures, NormalizationParameters&& params)
    : _figures(std::vector(figures)), _nparams(params)
    {
    }

    void TransformFigures(const TransformMatrix& transformMatrix);
    std::vector<Figure> GetFigures() const;
    NormalizationParameters GetNormalizationParams() const;
    void SetFigures(const std::vector<Figure>& figures);

private:
    NormalizationParameters _nparams;
    std::vector<Figure> _figures;
};
