#include "../io/FileReader.h"
#include <iostream>
#include <QApplication>
#include <QPainter>
#include <QTimer>

#include "core/RendererFacade.h"
#define PATH "/Users/k3rnel1x/Programming/oop_labs_bmstu/lab4/test_files/students_exams (вариант 2).csv"
using namespace std;

class Painter : public QWidget {
public:
    Painter()
    {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&Painter::update));

        timer->start(1);

        FacadeResult res = renderer.LoadScene(PATH, NormalizationParameters{});
        if (!res)
            throw std::runtime_error(res.GetErrorMessage());

    }

    void paintEvent(QPaintEvent* event) override
    {
        FacadeResult&& res = renderer.DrawScene();
        if (!res)
            throw std::runtime_error(res.GetErrorMessage());
    };

private:
    RendererFacade renderer {
        make_unique<FileReader>(),
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