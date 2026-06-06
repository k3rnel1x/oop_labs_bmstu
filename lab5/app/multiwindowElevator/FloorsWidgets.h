//
// Created by k3rnel1x on 05.06.2026.
//

#ifndef LAB5_FLOORSWIDGETS_H
#define LAB5_FLOORSWIDGETS_H
#include <QWidget>
#include <QButtonGroup>

#include "Floor.h"
#include <vector>

class FloorsWidgets : public QWidget {
    Q_OBJECT
public:

    explicit FloorsWidgets(int floors, int step, int gapsY, int gapsX);

    void show();
    QButtonGroup* getFloorsButtonsGroup() { return group; };

private:
    std::vector<Floor*> floors;
    QButtonGroup* group;
};


#endif //LAB5_FLOORSWIDGETS_H
