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

        FacadeResult res = renderer.LoadScene(OBJPATH, NormalizationParameters{});
        if (!res)
            throw std::runtime_error(res.GetErrorMessage());

    }

    void paintEvent(QPaintEvent* event) override
    {
        // FacadeResult res = renderer.RotateScene(0, 0, 0);
        // if (!res)
            // throw std::runtime_error(res.GetErrorMessage());

        FacadeResult res = renderer.DrawScene();
        if (!res)
            throw std::runtime_error(res.GetErrorMessage());
    };

private:
    RendererFacade renderer {
        make_unique<ObjFileReader>(),
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