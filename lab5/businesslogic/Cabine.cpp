#include "Cabine.h"

#include <iostream>
#include <QDebug>


Cabine::Cabine()
{
    qDebug() << "Cabine arrived on floor 1";
    connect(this, &Cabine::closeDoor, &_doors, &Doors::closeDoors);
    connect(&_doors, &Doors::closed, this, &Cabine::doorsClosed);

    connect(this, &Cabine::goMove, this, &Cabine::cabineMoving);

    connect(this, &Cabine::openDoor, &_doors, &Doors::openDoors);
    connect(&_doors, &Doors::opened, this, &Cabine::doorsOpened);
}

// Controller::goUp()
void Cabine::goUp()
{
    if (_state == MOVING)
        return;

    if (_state == STATEONFLOOR)
    {
        cabineMoving();
        return;
    }

    _direction = 1;
    emit closeDoor();
}

// Controller::goDown()
void Cabine::goDown()
{
    if (_state == MOVING)
        return;

    if (_currentFloor < 2)
    {
        emit cabineOnFloor(_currentFloor);
        return;
    }

    if (_state == STATEONFLOOR)
    {
        cabineMoving();
        return;
    }

    _direction = -1;
    emit closeDoor();
}

// Doors::closed()
void Cabine::doorsClosed()
{
    std::cout << "Doors closed" << std::endl;
    _state = MOVING;
    emit goMove();
}

// Cabine::goMove()
void Cabine::cabineMoving()
{
    std::cout << "Cabine moving" << std::endl;
    _currentFloor += _direction;
    QTimer::singleShot(MSECMOVING, this, &Cabine::onFloor);
}

// QTimer
void Cabine::onFloor()
{
    _state = STATEONFLOOR;
    emit cabineOnFloor(_currentFloor);
}

// Controller::arrive()
void Cabine::arriveCurr()
{
    emit openDoor();
}

// Doors::opened()
void Cabine::doorsOpened()
{
    std::cout << "Doors opened" << std::endl;
    _state = ARRIVED;
    emit arrivedOnFloor(_currentFloor);
}