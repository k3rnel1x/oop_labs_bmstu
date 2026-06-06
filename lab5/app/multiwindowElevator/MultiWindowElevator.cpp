//
// Created by k3rnel1x on 05.06.2026.
//

#include "MultiWindowElevator.h"

MultiWindowElevator::MultiWindowElevator(int floors)
{
    if (floors < 2 || floors > MAC_MAX_FLOORS)
        throw std::invalid_argument("Overfloors");

    elevator = new Elevator(floors);
    elevatorWindow = new ElevatorWindow(*elevator);

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    int floorStep = height/(floors+1);

    this->floors = new FloorsWidgets(floors, floorStep, GAPP, width/10 + 200 );

    QButtonGroup* group = this->floors->getFloorsButtonsGroup();
    connect(group, );

}

MultiWindowElevator::~MultiWindowElevator()
{
    delete elevator;
    delete elevatorWindow;
}

void MultiWindowElevator::show()
{
    elevatorWindow->show();
    floors->show();
}
