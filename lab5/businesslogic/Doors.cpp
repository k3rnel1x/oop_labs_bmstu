#include "Doors.h"

#include <QTimer>

// Cabine::closeDoor()
void Doors::closeDoors()
{
    emit closing();
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
    emit opening();
    QTimer::singleShot(DOORSTIME, this, &Doors::doorsOpened);
}
// QTimer
void Doors::doorsOpened()
{
    emit opened();
}
