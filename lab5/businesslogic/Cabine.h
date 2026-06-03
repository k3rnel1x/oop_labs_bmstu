#pragma once
#include <QObject>
#include <QTimer>
#include "Doors.h"
#define INITFLOOR 1
#define MSECMOVING 2000

class Cabine : public QObject {
    Q_OBJECT
enum CabineState {
    ARRIVED,
    STATEONFLOOR,
    MOVING,
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

    void arrivedOnFloor(int floor);
    void cabineOnFloor(int floor);
    void lockingDoors();
    void goMove();
    void arrived(int floor);

private:
    CabineState _state = ARRIVED;
    Doors _doors;
    int _currentFloor = INITFLOOR;
    int _targetFloor;
    int _direction;
};
