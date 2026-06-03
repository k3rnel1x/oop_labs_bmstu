#include <Controller.h>
#include <QApplication>

#include "Elevator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Elevator elevator{};
    elevator.call(7);
    elevator.call(3);
    elevator.call(1);
    elevator.call(2);
    // elevator.call(3);
    // elevator.call(4);
    elevator.call(5);
    // elevator.call(6);

    // elevator._controller.cabineArrivedOnFloor(0);

    return app.exec();
}
