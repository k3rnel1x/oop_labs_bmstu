#pragma once
#include <QObject>
#define DOORSTIME 1000

class Doors : public QObject {
Q_OBJECT
enum DoorsState {
    // OPENING,
    OPENED,
    // CLOSING,
    CLOSED
};
signals:
    void closing();
    void closed();
    void opening();
    void opened();

public slots:
    void closeDoors();
    void doorsClosed();
    void openDoors();
    void doorsOpened();

private:
    DoorsState _state = OPENED;
};
