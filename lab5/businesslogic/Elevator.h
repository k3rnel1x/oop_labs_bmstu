#pragma once
#include <QObject>

#include "Cabine.h"
#include "Controller.h"

class Elevator : public QObject {
Q_OBJECT
public:
    Elevator();

    void call(size_t floor);
    Cabine _cabine;
    Controller _controller;
signals:
    void _call(size_t floor);

};


