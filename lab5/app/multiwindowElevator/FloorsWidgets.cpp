//
// Created by k3rnel1x on 05.06.2026.
//

#include "FloorsWidgets.h"

#include <iostream>

FloorsWidgets::FloorsWidgets(int floors, int step, int gapsY, int gapsX)
{
    group = new QButtonGroup{};
    for (int n = floors; n >= 1; --n)
    {
        Floor* floor = new Floor{ n, step, gapsY, gapsX };
        this->floors.push_back(floor);
        group->addButton(floor->getButton(), n);
    }
}

void FloorsWidgets::show()
{
    for (auto& floor : this->floors)
        floor->show();
}
