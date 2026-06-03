#pragma once
#include <QObject>

class FloorCaller : public QObject {
Q_OBJECT
public:
signals:
    void call(int floor);
};