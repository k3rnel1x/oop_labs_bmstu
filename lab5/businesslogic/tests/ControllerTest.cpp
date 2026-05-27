#include <Controller.h>
#include <QApplication>
#include "FloorCaller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Cabine cabine;
    Controller controller(cabine);

    FloorCaller floor;
    QObject::connect(&cabine, &Cabine::call,
                     &controller, &Controller::handleCall);

    QObject::connect(&floor, &FloorCaller::call,
                     &controller, &Controller::handleCall);

    emit floor.call(1);
    emit cabine.call(2);
    emit cabine.call(2);
    emit floor.call(5);

    return app.exec();
}
