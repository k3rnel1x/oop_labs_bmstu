#pragma once
#include <queue>

#include "Cabine.h"

class Controller : public QObject {
Q_OBJECT
struct Command {
    size_t floor;
};

enum ControllerState {
    FREE,
    MOVING,
    UPDATINGTARGET,
    //
};
public:
    Controller(Cabine& cabine) : _controllingCabine(cabine) { };

public slots:
    void handleCall(size_t floor);
    void handleArrived();

private:
    void _processQueue();
    ControllerState _state = FREE;
    std::queue<Command> _commandsQueue;
    Cabine& _controllingCabine;
};
