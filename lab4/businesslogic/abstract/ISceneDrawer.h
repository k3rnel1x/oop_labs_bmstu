#pragma once
#include "../Scene.h"

class ISceneDrawer {
    virtual void DrawScene(const Scene& scene) = 0;
    virtual ~ISceneDrawer() = default;
};
