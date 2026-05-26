#include "RendererFacade.h"

FacadeResult&& RendererFacade::MoveScene(double x, double y, double z)
{
    TransformMatrix matrix = matrixBuilder.CreateMoveMatrix(x, y, z);
    _scene.TransformFigures(matrix);
}

FacadeResult && RendererFacade::RotateScene(double alpha, double beta, double gamma)
{
    TransformMatrix matrix = matrixBuilder.CreateRotationMatrix(alpha, beta, gamma);
    _scene.TransformFigures(matrix);
}

FacadeResult&& RendererFacade::ScaleScene(double a, double b, double c)
{
    TransformMatrix matrix = matrixBuilder.CreateScaleMatrix(a, b, c);
    _scene.TransformFigures(matrix);
}

void RendererFacade::SetSceneDrawer(std::unique_ptr<ISceneDrawer> scene_drawer)
{
    if (!scene_drawer)
        throw std::runtime_error("Scene drawer is null");

    _scene_drawer = std::move(scene_drawer);
}

FacadeResult&& RendererFacade::DrawScene()
{
    try
    {
         _scene_drawer->DrawScene(_scene);
    } catch (std::exception& e)
    {
        return FacadeResult{e.what()};
    }
    return FacadeResult{};
}

FacadeResult&& RendererFacade::LoadScene(std::string path, NormalizationParameters nparams)
{
    try
    {
        _scene = _file_reader->ReadScene(path, nparams);
    } catch (std::exception& e)
    {
        return FacadeResult{e.what()};
    }
    return FacadeResult{};
}
