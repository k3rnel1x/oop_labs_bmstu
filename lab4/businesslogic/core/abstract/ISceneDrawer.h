#pragma once
#include <core/Scene.h>

class ISceneDrawer {
    virtual void DrawScene(const Scene& scene) = 0;
    virtual ~ISceneDrawer() = default;
};
