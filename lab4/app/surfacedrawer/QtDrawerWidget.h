#pragma once
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <cmath>
#include <core/RendererFacade.h>

#define ROTATIONANGLE 0.05
#define STEP 2
#define PADD 30

class QtDrawerWidget: public QWidget {
public:
    QtDrawerWidget(std::unique_ptr<IFileReader> fileReader);

    void UnloadScene();
    void LoadScene(std::string path, NormalizationParameters nparams);
    void MoveScene  (double x, double y, double z);
    void RotateScene(double alpha, double beta, double gamma);
    void ScaleScene (double a, double b, double c);

    void paintEvent(QPaintEvent* event) override;
    NormalizationParameters GetNormalizationParameters();

private:
    std::unique_ptr<RendererFacade> _renderer;
};
