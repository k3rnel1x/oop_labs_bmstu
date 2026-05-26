#pragma once
#include <renderer/Scene.h>
class ISceneDrawer {
public:
    virtual void DrawScene(const Scene& scene) = 0;
    // virtual ~ISceneDrawer() = 0;
};
