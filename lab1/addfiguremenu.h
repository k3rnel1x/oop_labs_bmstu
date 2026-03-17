//
// Created by k3rnel1x on 17.03.2026.
//

#ifndef ADDFIGUREMENU_H
#define ADDFIGUREMENU_H

#include "libmenu/libmenu.h"
class AddCircle : public MenuItem {

public:
    AddCircle(Data* data) : MenuItem("Add circle", data)
    {
    }
    void run() override;
};

class AddRectangle : public MenuItem {
public:
    AddRectangle(Data* data) : MenuItem("Add rectangle", data)
    {
    }
    void run() override;
};

class AddTriangle : public MenuItem {
public:
    AddTriangle(Data* data) : MenuItem("Add triangle", data)
    {
    }

    void run() override;
};

class AddPolyAngle : public MenuItem {
public:
    AddPolyAngle(Data* data) : MenuItem("Add polyangle", data)
    {
    }

    void run() override;
};



#endif //ADDFIGUREMENU_H
