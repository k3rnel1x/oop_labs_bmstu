//
// Created by k3rnel1x on 02.05.2026.
//

#include "QtDrawerWidget.h"

QtDrawerWidget::QtDrawerWidget(std::unique_ptr<IFileReader> fileReader)
{
    auto drawer = std::make_unique<QtSceneDrawer>(this);
    _renderer = std::make_unique<RendererFacade>(
        std::move(fileReader), std::move(drawer)
        );

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&QtDrawerWidget::update));

    timer->start(1);
}

void QtDrawerWidget::UnloadScene()
{
    _renderer->UnloadScene();
}

void QtDrawerWidget::LoadScene(std::string path, NormalizationParameters nparams)
{
    FacadeResult res = _renderer->LoadScene(path, nparams);
    if(!res)
        throw std::runtime_error("Load scene failed: " + res.GetErrorMessage());
}

void QtDrawerWidget::MoveScene(double x, double y, double z)
{
    FacadeResult res = _renderer->MoveScene(x, y, z);
    if(!res)
        throw std::runtime_error("Move scene failed: " + res.GetErrorMessage());
}

void QtDrawerWidget::RotateScene(double alpha, double beta, double gamma)
{
    FacadeResult res = _renderer->RotateScene(alpha, beta, gamma);
    if(!res)
        throw std::runtime_error("Rotate scene failed:" + res.GetErrorMessage());
}

void QtDrawerWidget::ScaleScene(double a, double b, double c)
{
    FacadeResult res = _renderer->ScaleScene(a, b, c);
    if(!res)
        throw std::runtime_error("Scale scene failed:" + res.GetErrorMessage());
}

void QtDrawerWidget::paintEvent(QPaintEvent *event)
{
    FacadeResult res = _renderer->DrawScene();
    if(!res)
        throw std::runtime_error("Draw scene failed:" + res.GetErrorMessage());
}

NormalizationParameters QtDrawerWidget::GetNormalizationParameters()
{
    return _renderer->GetNormalizationParameters();
}