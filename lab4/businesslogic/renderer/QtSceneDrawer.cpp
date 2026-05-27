//
// Created by k3rnel1x on 26.05.2026.
//

#include "QtSceneDrawer.h"
#include <QCoreApplication>
#include <iostream>
#include <QPainter>

void QtSceneDrawer::DrawScene(const Scene &scene)
{
    if (!_canvas)
        throw std::runtime_error("Canvas is null");

    QPainter p;
    p.begin(_canvas);

    // std::cout << "!! ->> :" << scene.GetFigures()[0].GetVertices()[0].GetPosition().x << std::endl;
    for (auto& figure : scene.GetFigures())
    {
        Figure::FigureMetaInfo info = figure.GetMetaInfo();
        // std::cout << " x : (" << info.xMin << " " << info.xMax << ")";
        // std::cout << " y : (" << info.yMin << " " << info.yMax << ")";
        // std::cout << " z : (" << info.zMin << " " << info.zMax << ")";
        // std::cout << std::endl;

        for (auto& edge : figure.GetEdges())
        {
            // std::cout << edge.GetBegin().GetPosition().x << ' ' << edge.GetBegin().GetPosition().y << ' ' << edge.GetBegin().GetPosition().z << std::endl;
            std::pair begin = _processVertex(edge.GetBegin(), info);
            std::pair end = _processVertex(edge.GetEnd(), info);

            if (fabs(begin.first) < _canvas->width() && fabs(begin.second) < _canvas->height()
            &&  fabs(end.first) < _canvas->width() && fabs(end.second) < _canvas->height())
            {
                p.drawLine(begin.first, begin.second, end.first,   end.second);
            }
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

std::pair<int, int> QtSceneDrawer::_processVertex(Vertex vertex, Figure::FigureMetaInfo& info)
{
    Point3D point = vertex.GetPosition();
    std::swap(point.y, point.z);

    // Normalize to -1, 1
    // std::cout << info.xMax << " " << info.xMin << std::endl;
    point.x = SCALE*(-1 + ( point.x ) / ( info.xMax - info.xMin ) * 2);
    point.y = SCALE*(-1 + ( point.y ) / ( info.yMax - info.yMin ) * 2);
    point.z = -1 + (point.z)/( info.zMax - info.zMin )*2 + INITZ;

    // Protect
    std::pair<double, double> p = { (point.x / point.z), (point.y / point.z) };

    // Place (scale to display)
    std::pair<int, int> ipair;

    ipair.first =  int( (p.first  + 1)/2  * _canvas->width() );
    ipair.second = int( (p.second + 1)/2 * _canvas->height() );

    // std::cout << ipair.first << " " << ipair.second << std::endl;

    return ipair;
}
