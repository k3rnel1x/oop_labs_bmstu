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
    IDLE,
    // LOCKED,
    // UNLOCKED
};

public:
    Cabine();

public slots:
    void goUp();
    void goDown();

    void doorsClosed();
    void doorsOpened();
    void cabineMoving();
    void onFloor();
    void arriveCurr();

signals:
    void closeDoor();
    void openDoor();

    void arrivedOnFloor(size_t floor);
    void cabineOnFloor(size_t floor);
    void lockingDoors();
    void goMove();
    void arrived(size_t floor);

private:
    CabineState _state = IDLE;
    Doors _doors;
    size_t _currentFloor = INITFLOOR;
    size_t _targetFloor;
    int _direction;
};
