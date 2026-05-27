#include "../io/CsvFileReader.h"
#include <iostream>
#include <QApplication>
#include <QPainter>
#include <QTimer>

#include "core/RendererFacade.h"
#include "io/ObjFileReader.h"
#define CSVPATH "/Users/k3rnel1x/Programming/oop_labs_bmstu/lab4/test_files/students_exams (вариант 2).csv"
#define OBJPATH "/Users/k3rnel1x/Programming/oop_labs_bmstu/lab4/test_files/cube.obj"
using namespace std;

class Painter : public QWidget {
public:
    Painter()
    {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&Painter::update));

        timer->start(1);
        FacadeResult res = renderer.LoadScene(CSVPATH, NormalizationParameters{10, 100, 1, 1});
        if (!res)
            throw std::runtime_error(res.GetErrorMessage());

    }

    void paintEvent(QPaintEvent* event) override
    {
        FacadeResult res = renderer.RotateScene(0, 0, 0.002);
        if (!res)
            throw std::runtime_error(res.GetErrorMessage());

        res = renderer.MoveScene(0, -0.01, 0.001);
        if (!res)
            throw std::runtime_error(res.GetErrorMessage());

        res = renderer.ScaleScene(1, 1, 1.0005);
        if (!res)
            throw std::runtime_error(res.GetErrorMessage());

        res = renderer.DrawScene();
        if (!res)
            throw std::runtime_error(res.GetErrorMessage());
    };

private:
    RendererFacade renderer {
        make_unique<CsvFileReader>(),
        make_unique<QtSceneDrawer>(this)
    };;
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Painter painter{};
    painter.show();
    return app.exec();
}