#pragma once
#include <QObject>

#include "Cabine.h"
#include "Controller.h"

class Elevator : public QObject {
Q_OBJECT
public:
    Elevator(int floors);
    Cabine* getCabine() { return &_cabine; };
    int getFloorsCount() { return floorsCount; };

    void call(int floor);
    Cabine _cabine;
    Controller _controller;
public slots:
    void callFloorSlot(int floor);

signals:
    void _call(int floor);

private:
    int floorsCount;
};
