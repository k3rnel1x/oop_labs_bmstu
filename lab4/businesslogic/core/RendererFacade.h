#include <string>

#include "FacadeResult.h"
#include <io/NormalizationParams.h>
#include <io/FileReader.h>
#include <core/abstract/ISceneDrawer.h>

class RendererFacade
{
public:
    RendererFacade(/* args */);
    ~RendererFacade();

    FacadeResult&& DrawScene();

    FacadeResult&& LoadScene(std::string path, NormalizationParameters nparams);
    FacadeResult&& MoveScene  (double x, double y, double z);
    FacadeResult&& RotateScene(double x, double y, double z);
    FacadeResult&& ScaleScene (double x, double y, double z);

private:
    /* data */
    FileReader _file_reader;
    ISceneDrawer _scene_drawer;
    Scene _scene;
};
