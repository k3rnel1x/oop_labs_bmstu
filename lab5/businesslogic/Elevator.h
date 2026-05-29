#pragma once
#include <QObject>

#include "Cabine.h"
#include "Controller.h"

class Elevator : public QObject {
public:
    Elevator();
signals:
    void call(size_t floor);

private:
    Cabine _cabine;
    Controller _controller;
};


