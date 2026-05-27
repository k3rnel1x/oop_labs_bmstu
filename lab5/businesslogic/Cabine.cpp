//
// Created by k3rnel1x on 27.05.2026.
//

#include "Cabine.h"

#include <iostream>
#include <thread>

void Cabine::_moveToTarget(size_t floor)
{
    if (_state == STOPPED && _currentFloor != floor)
    {
        _doors.close();

        _state = MOVING;
        std::cout << "Cabinee moving.. " << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
        _doors.open();

        _currentFloor = floor;
        std::cout << "Cabinee on " << _currentFloor << " floor" << std::endl;

        _state = STOPPED;
    }
}
