#pragma once

#include <string>
#include "FacadeResult.h"
#include <io/NormalizationParams.h>
#include <io/CsvFileReader.h>
#include <renderer/QtSceneDrawer.h>
#include <renderer/Scene.h>
#include "math/TransformMatrixBuilder.h"

class RendererFacade{
public:
    RendererFacade(std::unique_ptr<IFileReader> fileReader, std::unique_ptr<ISceneDrawer> sceneDrawer) :
    _file_reader(std::move(fileReader)), _scene_drawer(std::move(sceneDrawer))
    {
    };

    void SetSceneDrawer(std::unique_ptr<ISceneDrawer> _scene_drawer);
    FacadeResult DrawScene();

    FacadeResult LoadScene(std::string path, NormalizationParameters nparams);
    void UnloadScene();
    FacadeResult MoveScene  (double x, double y, double z);
    FacadeResult RotateScene(double alpha, double beta, double gamma);
    FacadeResult ScaleScene (double a, double b, double c);

private:
    /* data */
    TransformMatrixBuilder matrixBuilder;
    std::unique_ptr<IFileReader>  _file_reader;
    std::unique_ptr<ISceneDrawer> _scene_drawer;
    Scene _scene;
};
