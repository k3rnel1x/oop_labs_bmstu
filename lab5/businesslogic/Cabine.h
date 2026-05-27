#pragma once
#include <QObject>
#include <QTimer>
#include "Doors.h"
#define INITFLOOR 0
#define MSECMOVING 2000

class Cabine : public QObject {
    Q_OBJECT
enum CabineState {
    MOVING,
    STOPPED,
    PREPARINGTOMOVE,
    LOCKED,
    UNLOCKED
};

public:
    void _moveToTarget(size_t floor);

signals:
    void call(size_t floor);

private:
    CabineState _state = STOPPED;
    Doors _doors;
    size_t _currentFloor = INITFLOOR;
};
