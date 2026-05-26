#include <string>

#include "FacadeResult.h"
#include <io/NormalizationParams.h>
#include <io/FileReader.h>
#include <renderer/QtSceneDrawer.h>
#include <renderer/Scene.h>

class RendererFacade
{
public:
    RendererFacade(std::unique_ptr<IFileReader> file_reader) :
    _file_reader(std::move(file_reader))
    {
    };

    ~RendererFacade();

    void SetSceneDrawer(std::unique_ptr<ISceneDrawer> _scene_drawer);
    FacadeResult&& DrawScene(const Scene& scene);

    FacadeResult&& LoadScene(std::string path, NormalizationParameters nparams);
    FacadeResult&& MoveScene  (double x, double y, double z);
    FacadeResult&& RotateScene(double x, double y, double z);
    FacadeResult&& ScaleScene (double x, double y, double z);

private:
    /* data */
    std::unique_ptr<IFileReader>  _file_reader;
    std::unique_ptr<ISceneDrawer> _scene_drawer;
    Scene _scene;
};
