#include "Controller.h"
#include <iostream>
#include <algorithm>

void Controller::start()
{
    if (_state == FREE)
    {
        if (_cabineFloor == _queue.front())
        {
            cabineArrivedOnFloor(_cabineFloor);
            return;
        }

        _state = BUSY;
        _targetFloor = _getClosestTarget();
        std::cout << "Set target " << _targetFloor << std::endl;
        emit goUp();
    }
}

// Cabine::arrivedOnFloor(size_t floor)
void Controller::cabineArrivedOnFloor(size_t floor)
{
    qDebug() << "Cabine arrived on floor" << floor;
    if (_queue.empty())
    {
        qDebug() << "Queue is empty";
        _state = FREE;
        return;
    }

    _targetFloor = _getClosestTarget();
    std::cout << "Set target " << _targetFloor << std::endl;
    emit goUp();
}

// Cabine::cabineOnFloor(size_t floor)
void Controller::cabineOnFloor(size_t floor)
{
    std::cout << "Cabine on floor " << floor << std::endl;
    // _targetFloor = _getClosestTarget();

    bool flag = std::find(_queue.begin(), _queue.end(), floor) != _queue.end();
    if (floor == _targetFloor || flag)
    {
        std::cout << "Deleting from queue " << floor << std::endl;
        std::erase(_queue, floor);
        emit arrive();
        return;
    }

    emit goUp();
}

void Controller::setCabineFloor(size_t floor)
{
    _cabineFloor = floor;
}

void Controller::addTarget(size_t floor)
{
    std::cout << "Added target: " << floor << std::endl;
    // std::stack<size_t> stack;
    // while (!_queue.empty() && _queue.front() > floor)
    // {
    //     stack.push(_queue.front());
    //     _queue.pop_front();
    // }

    _queue.push_back(floor);
    //
    // while (!stack.empty())
    // {
    //     _queue.push_front(stack.top());
    //     stack.pop();
    // }

    std::sort(_queue.begin(), _queue.end());
    std::cout << "Queue: ";
    for (auto uint : _queue)
        std::cout << uint << ' ';
    std::cout << std::endl;
}

size_t Controller::_getClosestTarget()
{
    if (_queue.empty())
        return _targetFloor;

    size_t closestFloor = _queue.front();
    int distance = abs(int(_targetFloor) - int(closestFloor));
    for (size_t floor : _queue)
    {
        int curr = abs(int(_targetFloor) - int(floor));
        if (curr < distance)
        {
            closestFloor = floor;
            distance = curr;
        }
    }

    return closestFloor;
}

int Controller::_getDirection()
{
    return 1;
}
