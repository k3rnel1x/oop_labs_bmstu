#include "ElevatorWindow.h"
#include <QApplication>
#include <qboxlayout.h>
#include <QPushButton>
#include <QKeyEvent>
#include <QButtonGroup>

ElevatorWindow::ElevatorWindow(Elevator& elevator) :
    elevator{ elevator }
{
    floorsButtons = new QButtonGroup {};


    // init buttons
    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QLayout* verticalLayout = new QVBoxLayout{this};

    floorIndicator = new QLabel { "1" };
    verticalLayout->addWidget(floorIndicator);

    for (int n = elevator.getFloorsCount(); n >= 1; --n)
    {
        QPushButton* button = new QPushButton { QString::number(n) };
        floorsButtons->addButton(button, n-1);
        button->setSizePolicy(policy);
        verticalLayout->addWidget(button);
    }
    doorsIndicator = new QLabel {"Doors Opened"};
    verticalLayout->addWidget(doorsIndicator);

    connect(floorsButtons, &QButtonGroup::idClicked, this, &ElevatorWindow::floorClicked);
    cabine = elevator.getCabine();
    Doors* doors = cabine->getDoors();
    connect(doors, &Doors::closing, this, &ElevatorWindow::startDoorsClosing);
    connect(doors, &Doors::opening, this, &ElevatorWindow::startDoorsOpening);
    connect(cabine, &Cabine::arrivedOnFloor, this, &ElevatorWindow::updateArrivedFloor);
    connect(cabine, &Cabine::startMoving, this, &ElevatorWindow::startMoving);

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->screenWidth = screenGeometry.width();
    this->screenHeight = screenGeometry.height();

    floorStep = screenHeight / (elevator.getFloorsCount()+1);
    this->setFixedSize(200, floorStep + 50);

    x = screenWidth/10;
    y = screenHeight - floorStep - this->height() / 2;
    this->move(x, y);
    speed = (MSECMOVING-DOORSTIME) / floorStep * 2;

    updateCabinePosTimer = new QTimer{};

    connect(updateCabinePosTimer, &QTimer::timeout, this, [this]() {
        y += direction;
        this->move(x,y);
    });

    // floors = new FloorsWidgets{elevator.getFloorsCount(), floorStep, 150, GAPP, 350};
    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint
                          | Qt::WindowTitleHint);

}

ElevatorWindow::~ElevatorWindow()
{
}

void ElevatorWindow::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    switch (key)
    {
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5: {
            elevator.call(key - '0');
        }
    }
}

void ElevatorWindow::closeEvent(QCloseEvent* event)
{
    QApplication::exit();
}

void ElevatorWindow::moveEvent(QMoveEvent *event)
{
    QWidget::moveEvent(event);
    this->move(x,y);
}

void ElevatorWindow::floorClicked(int id)
{
    elevator.call(id + 1);
}

void ElevatorWindow::updateArrivedFloor(int floor)
{

}

void ElevatorWindow::processArrive(int floor)
{
    updateCabinePosTimer->stop();

    y = screenHeight - this->height()/2 - floorStep*(floor) - GAPP;
    this->move(x, y);

    QTimer::singleShot(DOORSTIME, this, [this]() {
        this->doorsIndicator->setText("Doors Opened");
    });

    currFloor = floor;
    floorIndicator->setText(QString::number(floor));
}


void ElevatorWindow::startDoorsOpening()
{
    processArrive(currFloor = cabine->getCurrentFloor());
}

void ElevatorWindow::startDoorsClosing()
{
    QTimer::singleShot(DOORSTIME, this, [this]() {
        this->doorsIndicator->setText("Doors Closed");
    });
}

void ElevatorWindow::startMoving(int direction)
{
    this->direction = -direction;
    updateCabinePosTimer->start(speed);
}