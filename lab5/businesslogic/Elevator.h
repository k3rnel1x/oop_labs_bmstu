#pragma once
#include <QObject>

#include "Cabine.h"
#include "Controller.h"

class Elevator : public QObject {
Q_OBJECT
public:
    Elevator();

    Cabine _cabine;
    Controller _controller;
signals:
    void call(size_t floor);

// private:

};


