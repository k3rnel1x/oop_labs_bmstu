#pragma once
#include <QObject>
#include <QDebug>
#include <queue>

class Controller : public QObject {
Q_OBJECT

enum ControllerState {
    FREE,
    BUSY
};

signals:
    void goDown();
    void goUp();
    void arrive();

public slots:
    void start();
    void cabineArrivedOnFloor(size_t floor);
    void cabineOnFloor(size_t floor);
    void setCabineFloor(size_t floor);

    void addTarget(size_t floor);

private:
    size_t _getClosestTarget();
    int _getDirection();
    ControllerState _state = FREE;
    std::deque<size_t> _queue;
    size_t _targetFloor;
    size_t _cabineFloor{1};
};
