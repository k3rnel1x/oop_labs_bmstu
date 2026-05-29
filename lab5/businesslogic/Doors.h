#pragma once
#include <QObject>

class Doors : public QObject {
Q_OBJECT
enum DoorsState {
    // OPENING,
    OPENED,
    // CLOSING,
    CLOSED
};
signals:
    // void closing();
    void closed();
    // void opening();
    void opened();

public slots:
    void closeDoors();
    void doorsClosed();
    void openDoors();
    void doorsOpened();

private:
    DoorsState _state = OPENED;
};
