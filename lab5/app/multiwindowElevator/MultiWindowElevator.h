#pragma once
#include <QWidget>

#include "ElevatorWindow.h"
#define MAC_MAX_FLOORS 6

class MultiWindowElevator : QObject {
Q_OBJECT
public:
    MultiWindowElevator(int floors);
    ~MultiWindowElevator();

    void show();

private:
    Elevator* elevator;
    ElevatorWindow* elevatorWindow;
    FloorsWidgets* floors;
};
