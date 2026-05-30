#include <iostream>
#include <renderer/QtSceneDrawer.h>
#include <QWidget>
#include <QApplication>
#include <qevent.h>
#include <QPainter>
#include <QTimer>

#include "core/RendererFacade.h"
#define PATH1 "/Users/k3rnel1x/Programming/oop_labs_bmstu/lab4/test_files/schools_exams (вариант 1).csv"
#define PATH2 "/Users/k3rnel1x/Programming/oop_labs_bmstu/lab4/test_files/students_exams (вариант 2).csv"

using namespace std;

class Painter : public QWidget {
public:
    Painter(Scene scene) : _scene(scene), _drawer(this)
    {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&Painter::update));

        timer->start(1);
    }
    void paintEvent(QPaintEvent* event) override
    {
        this->_drawer.DrawScene(_scene);
        // _scene.TransformFigures(TransformMatrixBuilder::CreateRotationMatrix(0, 0, 0.01));
        // _scene.TransformFigures(TransformMatrixBuilder::CreateScaleMatrix(1, 1, 1));
    }

private:
    QtSceneDrawer _drawer;
    Scene _scene;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CsvFileReader reader;
    Scene scene;
    try
    {
        scene = reader.ReadScene(PATH2, NormalizationParameters{0, 40, 1, 1});
    } catch (exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    Painter painter(scene);

    painter.show();

    return app.exec();
}