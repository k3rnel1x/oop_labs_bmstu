#pragma once
#include <QObject>
#include <queue>

class Controller : public QObject {
Q_OBJECT

enum ControllerState {
    FREE,
    MOVING,
    UPDATINGTARGET,
};

signals:
    void goDown();
    void goUp();
    void arrive();

public slots:
    void cabineArrivedOnFloor(size_t floor);
    void cabineOnFloor(size_t floor);

    void addTarget(size_t floor);

private:
    int _getDirection();
    ControllerState _state = FREE;
    std::deque<size_t> _queue;
    size_t _targetFloor;
};
