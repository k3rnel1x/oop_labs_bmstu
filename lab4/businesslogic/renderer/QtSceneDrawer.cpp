//
// Created by k3rnel1x on 26.05.2026.
//

#include "QtSceneDrawer.h"
#include <QPainter>

void QtSceneDrawer::DrawScene(const Scene& scene)
{
    if (!_canvas)
        throw std::runtime_error("Canvas is null");

    QPainter p;
    p.begin(_canvas);

    for (auto& figure : scene.GetFigures())
    {
        for (auto& edge : figure.GetEdges())
        {
            std::pair begin = _processVertex(edge.GetBegin());
            std::pair end = _processVertex(edge.GetEnd());
            p.drawLine(begin.first, begin.second,
                       end.first,   end.second);
            // qDebug() << "Placed: " << std::to_string(placedBegin.first) << std::to_string(placedBegin.second);
        }
    }

    p.end();
}

void QtSceneDrawer::SetCanvas(QWidget *canvas)
{
    if (!canvas)
        throw std::runtime_error("Canva s is null");

    this->_canvas = canvas;
}

std::pair<int, int> QtSceneDrawer::_processVertex(const Vertex& vertex)
{
    Point3D point = vertex.GetPosition();
    double scale = 3; // TODO
    std::swap(point.y, point.z);

    // Normalize
    point.x = scale*(-1 + (point.x)/double(30)*2);
    point.y = scale*(-1 + (point.y)/double(30)*2);
    point.z = -1 + (point.z)/(ZMAX)*2 + INITZ;

    // Protect
    std::pair<double, double> p = { (point.x / point.z), (point.y / point.z) };

    // Place (scale to display)
    std::pair<int, int> ipair;
    ipair.first =  int( (p.first  + 1)/2  * _canvas->width() );
    ipair.second = int( (p.second + 1)/2 * _canvas->height() );

    return ipair;
}
