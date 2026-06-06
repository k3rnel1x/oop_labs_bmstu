//
// Created by k3rnel1x on 05.06.2026.
//

#include "Floor.h"

#include <QVBoxLayout>

Floor::Floor(int floor, int step, int gapsY, int gapsX)
{
    this->resize(400, 20);
    this->setFixedSize(400, 20);
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenHeight = screenGeometry.height();

    x = gapsX;
    y = screenHeight - floor*step + gapsY + this->height();
    QLabel* label = new QLabel { QString::number(floor)};

    QLayout* layout = new QHBoxLayout{this};
    layout->addWidget(label);
    layout->setContentsMargins(10, 5, 10, 5);

    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint
                   | Qt::WindowTitleHint);

    button = new FloorButton { floor, this->x, this->y - step + 50 };
    button->show();
}

Floor::FloorButton::FloorButton(int floor, int x, int y)
{
    this->setText(QString::number(floor));
    this->setFixedSize(50, 50);
    this->x = x;
    this->y = y;

    this->move(x, y);
}

void Floor::FloorButton::closeEvent(QCloseEvent *event)
{
    QPushButton::closeEvent(event);
    QApplication::exit();
}

void Floor::FloorButton::moveEvent(QMoveEvent *event)
{
    QPushButton::moveEvent(event);
    QWidget::moveEvent(event);
    this->move(x, y);
}

void Floor::closeEvent(QCloseEvent* event)
{
    QApplication::exit();
}

void Floor::moveEvent(QMoveEvent *event)
{
    QWidget::moveEvent(event);
    this->move(x, y);
}