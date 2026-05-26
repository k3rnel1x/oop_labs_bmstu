#pragma once
#include "abstract/ISceneDrawer.h"
#include <QWidget>

#define ZMAX   100
#define INITZ -2.0

class QtSceneDrawer : public ISceneDrawer {
public:
    QtSceneDrawer() = default;
    QtSceneDrawer(QWidget* canvas) : _canvas(canvas)
    {
    };

    void DrawScene(const Scene& scene) override;
    void SetCanvas(QWidget* canvas);

private:
    std::pair<int, int> _processVertex(const Vertex& vertex);
    QWidget* _canvas;
};
