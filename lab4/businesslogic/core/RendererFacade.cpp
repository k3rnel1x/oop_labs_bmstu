#include "RendererFacade.h"

void RendererFacade::SetSceneDrawer(std::unique_ptr<ISceneDrawer> scene_drawer)
{
    if (!scene_drawer)
        throw std::runtime_error("Scene drawer is null");

    _scene_drawer = std::move(scene_drawer);
}
