//
// Created by k3rnel1x on 27.05.2026.
//

#include "Controller.h"

void Controller::handleCall(size_t floor)
{
    _commandsQueue.push(Command{floor});
    _processQueue();
}

void Controller::handleArrived()
{
    _processQueue();
}

void Controller::_processQueue()
{
    if (_commandsQueue.empty()) return;

    Command command = _commandsQueue.front();

    _controllingCabine._moveToTarget(command.floor);

    _commandsQueue.pop();

    _processQueue();
}
