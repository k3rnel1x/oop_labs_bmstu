#include "RendererFacade.h"

#include <iostream>

FacadeResult RendererFacade::MoveScene(double x, double y, double z)
{
    try
    {
        TransformMatrix matrix = matrixBuilder.CreateMoveMatrix(x, y, z);
        _scene.TransformFigures(matrix);

    } catch (std::exception& e)
    {
        return FacadeResult{e.what()};
    } catch (std::runtime_error& e)
    {
        return FacadeResult{e.what()};
    }

    return FacadeResult{};
}

FacadeResult RendererFacade::RotateScene(double alpha, double beta, double gamma)
{
    try
    {
        TransformMatrix matrix = matrixBuilder.CreateRotationMatrix(alpha, beta, gamma);
        // matrix.printToStdout();
        _scene.TransformFigures(matrix);

    } catch (std::exception& e) {
        return FacadeResult{e.what()};
    }
    return FacadeResult{};
}

FacadeResult RendererFacade::ScaleScene(double a, double b, double c)
{
    try
    {
        TransformMatrix matrix = matrixBuilder.CreateScaleMatrix(a, b, c);
        _scene.TransformFigures(matrix);
    } catch (std::exception& e)
    {
        return FacadeResult{e.what()};
    }
    return FacadeResult{};
}

NormalizationParameters RendererFacade::GetNormalizationParameters() const
{
    return _scene.GetNormalizationParams();
}

void RendererFacade::SetSceneDrawer(std::unique_ptr<ISceneDrawer> scene_drawer)
{
    if (!scene_drawer)
        throw std::runtime_error("Scene drawer is null");

    _scene_drawer = std::move(scene_drawer);
}

FacadeResult RendererFacade::DrawScene()
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

FacadeResult RendererFacade::LoadScene(std::string path, NormalizationParameters nparams)
{
    try
    {
        this->_scene = _file_reader->ReadScene(path, nparams);
    } catch (std::exception& e)
    {
        return FacadeResult{e.what()};
    }
    return FacadeResult{};
}

void RendererFacade::UnloadScene()
{
    _scene = Scene(std::vector<Figure>(), NormalizationParameters{});
}
