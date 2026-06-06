#include "Controller.h"
#include <iostream>
#include <algorithm>
#include <QTimer>

void Controller::start()
{
    if (_state == FREE)
    {
        if (_cabineFloor == _targetFloor)
        {
            cabineArrivedOnFloor(_cabineFloor);
            return;
        }

        _state = BUSY;
        _targetFloor = _getClosestTarget();
#ifdef LOGGER
        std::cout << "Set target " << _targetFloor << std::endl;
#endif
        if (_cabineFloor == _targetFloor)
        {
            cabineArrivedOnFloor(_cabineFloor);
            return;
        }

        direction = int(_targetFloor) - int(_cabineFloor) > 0? 1 : -1;
        if (direction > 0)
            emit goUp();
        else
            emit goDown();
    }
}

// Cabine::arrivedOnFloor(int floor)
void Controller::cabineArrivedOnFloor(int floor)
{
    qDebug("Cabine arrived on floor %i", floor);

    std::erase(_queue, floor);
    qDebug("Queue: ");
    for (auto uint : _queue)
        qDebug("%i ", uint);
    qDebug() << " ";

    if (_queue.empty())
    {
#ifdef LOGGER
        qDebug() << "Queue is empty";
#endif
        _state = FREE;

        if (_cabineFloor)
        {
            QTimer::singleShot(CABINEWAITMSEC, this, [&]() {
                this->addTarget(1);
            });
        }
        return;
    }


    _targetFloor = _getClosestTarget();
#ifdef LOGGER
    std::cout << "Set target " << _targetFloor << std::endl;
#endif
    if (_cabineFloor == _targetFloor)
    {
        cabineArrivedOnFloor(_targetFloor);
        return;
    }

    direction = int(_targetFloor) - int(_cabineFloor) > 0? 1 : -1;

    QTimer::singleShot(CABINEWAITMSEC, this, [&]() {
        if (direction > 0)
            emit goUp();
        else
            emit goDown();
    });
}

// Cabine::cabineOnFloor(int floor)
void Controller::cabineOnFloor(int floor)
{
    _state = BUSY;
#ifdef LOGGER
    std::cout << "Cabine on floor " << floor << std::endl;
#endif

    bool flag = std::find(_queue.begin(), _queue.end(), floor) != _queue.end();
    if (floor == _targetFloor || flag)
    {
#ifdef LOGGER
        std::cout << "Deleting from queue " << floor << std::endl;
#endif
        // std::erase(_queue, floor);

        emit arrive();
        return;
    }

    direction = int(_targetFloor) - int(_cabineFloor) > 0? 1 : -1;
    if (direction > 0)
        emit goUp();
    else
        emit goDown();
}

void Controller::setCabineFloor(int floor)
{
    _cabineFloor = floor;
    qDebug("Cabine set floor %i", floor);
}

void Controller::addTarget(int floor)
{
    if (_state == FREE && _cabineFloor == floor)
        return;

    bool isExist = std::find(_queue.begin(), _queue.end(), floor) != _queue.end();

    if (isExist)
        return;

    _queue.push_back(floor);
#ifdef LOGGER
    std::cout << "Added target: " << floor << std::endl;
#endif

    std::sort(_queue.begin(), _queue.end());

#ifdef LOGGER
    std::cout << "Queue: ";
    for (auto uint : _queue)
        std::cout << uint << ' ';
    std::cout << std::endl;
#endif
    if (_state == FREE && _cabineFloor == _targetFloor)
    {
        emit start();
        // qDebug("emit start();");
    }
}

int Controller::_getClosestTarget()
{
    if (_queue.empty())
        return _targetFloor;

    int closestFloor = _queue.front();
    int distance = abs(int(_targetFloor) - int(closestFloor));
    for (int floor : _queue)
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