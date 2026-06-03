#include "Doors.h"

#include <QTimer>

// Cabine::closeDoor()
void Doors::closeDoors()
{
    QTimer::singleShot(DOORSTIME, this, &Doors::doorsClosed);
}
// QTimer
void Doors::doorsClosed()
{
    emit closed();
}

// Cabine::openDoor()
void Doors::openDoors()
{
    QTimer::singleShot(DOORSTIME, this, &Doors::doorsOpened);
}
// QTimer
void Doors::doorsOpened()
{
    emit opened();
}
