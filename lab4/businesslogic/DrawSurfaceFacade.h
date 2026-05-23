#include <string>

#include "abstract/IFacadeResult.h"
#include "NormalizationParams.h"

class DrawSurfaceFacade
{
public:
    DrawSurfaceFacade(/* args */);
    ~DrawSurfaceFacade();

    FacadeResult&& DrawScene();
    FacadeResult&& LoadScene(std::string path, NormalizationParameters nparams);
    FacadeResult&& MoveScene  (double x, double y, double z);
    FacadeResult&& RotateScene(double x, double y, double z);
    FacadeResult&& ScaleScene (double x, double y, double z);

private:
    /* data */
    IFileReader _file_reader;
    ISceneDrawer _scene_drawer;
    Scene _scene;
};
