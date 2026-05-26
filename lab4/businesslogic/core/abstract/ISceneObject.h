#pragma once
#include <math/TransformMatrix.h>

class ISceneObject {
public:
    virtual void Transform(const TransformMatrix& transformMatrix) = 0;
    virtual ~ISceneObject() = default;
};
