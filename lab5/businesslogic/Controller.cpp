#include "Controller.h"

#include <iostream>

// Cabine::arrivedOnFloor(size_t floor)
void Controller::cabineArrivedOnFloor(size_t floor)
{
    std::cout << "Cabine arrived on floor " << floor << std::endl;
    if (_queue.empty())
        return;

    _targetFloor = _queue.front();
    std::cout << "Set target " << _targetFloor << std::endl;
    emit goUp();
}

// Cabine::cabineOnFloor(size_t floor)
void Controller::cabineOnFloor(size_t floor)
{
    std::cout << "Cabine on floor " << floor << std::endl;
    if (floor == _targetFloor)
    {
        _queue.pop_front();
        emit arrive();
        return;
    }

    emit goUp();
}

void Controller::addTarget(size_t floor)
{
    std::cout << "Added target: " << floor << std::endl;
    _queue.push_back(floor);
}

int Controller::_getDirection()
{
    return 1;
}
