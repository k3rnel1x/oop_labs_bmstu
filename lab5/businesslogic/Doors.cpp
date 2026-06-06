#include "Doors.h"

#include <QTimer>

// Cabine::closeDoor()
void Doors::closeDoors()
{
    if (_state == CLOSED)
    {
        emit closed();
        return;
    }

    emit closing();
    QTimer::singleShot(DOORSTIME, this, &Doors::doorsClosed);
}
// QTimer
void Doors::doorsClosed()
{
    _state = CLOSED;
    emit closed();
}

// Cabine::openDoor()
void Doors::openDoors()
{
    if (_state == OPENED)
    {
        emit opened();
        return;
    }

    emit opening();
    QTimer::singleShot(DOORSTIME, this, &Doors::doorsOpened);
}
// QTimer
void Doors::doorsOpened()
{
    _state = OPENED;
    emit opened();
}
