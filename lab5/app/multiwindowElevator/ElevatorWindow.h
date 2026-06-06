#pragma once

#include <QButtonGroup>
#include <Elevator.h>
#include <QWidget>
#include <Elevator.h>
#include <QLabel>
#include <Cabine.h>

#include "FloorsWidgets.h"

#define GAPP 40

class ElevatorWindow : public  QWidget {
    Q_OBJECT
public:
    ElevatorWindow(Elevator& elevator);
    void keyPressEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void processArrive(int floor);

    ~ElevatorWindow();

public slots:
    void floorClicked(int id);
    void updateArrivedFloor(int floor);

    void startDoorsOpening();

    void startDoorsClosing();

    void startMoving(int direction);
    //
    // void cabineOnFloor(int floor);

private:
    int x, y;
    int direction;

    int floorStep;
    int speed;
    int currFloor = 1;
    Elevator& elevator;
    QButtonGroup* floorsButtons;
    int screenWidth, screenHeight;
    QLabel* doorsIndicator;
    QLabel* floorIndicator;

    Cabine* cabine;
    QTimer* updateCabinePosTimer;

    // FloorsWidgets* floors;
};
