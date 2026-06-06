//
// Created by k3rnel1x on 29.05.2026.
//

#include "Elevator.h"
Elevator::Elevator(int floors)
{
    this->floorsCount = floors;

    connect(&_controller, &Controller::goUp, &_cabine, &Cabine::goUp);
    connect(&_controller, &Controller::goDown, &_cabine, &Cabine::goDown);
    connect(&_controller, &Controller::arrive, &_cabine, &Cabine::arriveCurr);

    connect(&_cabine, &Cabine::cabineOnFloor, &_controller, &Controller::cabineOnFloor);
    connect(&_cabine, &Cabine::arrivedOnFloor, &_controller, &Controller::cabineArrivedOnFloor);
    connect(&_cabine, &Cabine::arrivedOnFloor, &_controller, &Controller::setCabineFloor);

    connect(this, &Elevator::_call, &_controller, &Controller::addTarget);
    // connect(this, &Elevator::_call, &_controller, &Controller::start);
}

void Elevator::call(int floor)
{
    if (1 <= floor && floor <= floorsCount)
        emit _call(floor);
}

void Elevator::callFloorSlot(int floor)
{
    call (floor);
}
