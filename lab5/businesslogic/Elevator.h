#pragma once
#include <QObject>

#include "Cabine.h"
#include "Controller.h"
#define FLOORSCOUNT 5

class Elevator : public QObject {
Q_OBJECT
public:
    Elevator();

    void call(int floor);
    Cabine _cabine;
    Controller _controller;
signals:
    void _call(int floor);

};


