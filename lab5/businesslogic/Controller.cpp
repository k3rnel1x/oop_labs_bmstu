//
// Created by k3rnel1x on 27.05.2026.
//

#include "Controller.h"
#include <algorithm>

void Controller::cabineArrivedOnFloor(size_t floor)
{
    if (_queue.empty())
        return;

    size_t next = _getNextTarget();
    while (next == floor) next = _getNextTarget();
    _targetFloor = next;

    emit gotoFloor(next);
}

void Controller::cabineOnFloor(size_t floor)
{
    if (floor == _targetFloor)
    {
        cabineArrivedOnFloor(floor);
        return;
    }

    // auto iter = std::find(_queue.begin(), _queue.end(), floor);
    // if (iter != _queue.end() && *iter != _targetFloor)
    // {
    //     _queue.erase(iter);
    //     emit arriveCurr();
    //     return;
    // }

    emit gotoFloor(++floor);
}

int Controller::_getDirection()
{
    return 1;
}

void Controller::addTarget(size_t floor)
{
    _queue.push_back(floor);

    _getDirection()? emit goUp() : emit goDown();
}