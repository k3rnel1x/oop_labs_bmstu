#pragma once
#include "../TransformMatrix.h"

class SceneObject {
public:
    virtual void Transform(TransformMatrix transformMatrix) = 0;
    virtual ~SceneObject() = default;
};
