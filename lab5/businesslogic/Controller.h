#pragma once
#include <QObject>
#include <QDebug>

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
    void cabineArrivedOnFloor(int floor);
    void cabineOnFloor(int floor);
    void setCabineFloor(int floor);

    void addTarget(int floor);

private:
    int _getClosestTarget();
    int direction = 1;
    ControllerState _state = FREE;
    std::deque<int> _queue;
    int _targetFloor{1};
    int _cabineFloor{1};
};
