#include <iostream>
#include "finny_geometry.h"

class Data {
private:
    std::vector<Figure*> _appdata;
};

class Action : public Data {
public:
    virtual void run() = 0;
};

class Input : public Action {
public:
    void clear() { std::cout.clear(); }
    virtual void run() = 0;
};

class MenuItem : public Action {
public:
    MenuItem(std::string name)
    {
        if (name.empty())
            throw std::invalid_argument("Name must be non-emply.");

        _name = name;
    }

    void show() // TODO Implement MenuItem::show
    {
    };

    void run()
    {
        show();
    };
private:
    std::string _name;
};

class MenuList : public MenuItem {
typedef std::vector<MenuItem> MenuItemsList;
public:
    MenuList(std::string name) :
    MenuItem(name)
    {
    }

    void add_item(MenuItem menu_item)
    {
        _menu_items.push_back(menu_item);
    }
private:
    MenuItemsList _menu_items;
};

////

class Sort : public Action {
public:
    Sort() = delete;
    ~Sort() = delete;
    Sort(const Sort&) = delete;

    void run() override; // TODO Implement Sort::run
};

class DelByPerimeter : public Action {
public:
    void run() override; // TODO Implement DelByPerimeter::run
};

class ShowFigures : public Input {
public:
    void show();         // TODO Implement DelByPerimeter::show and show_perimeters
    void show_perimeters();
};

////
class InputAction : public Input { // TODO Implement InputAction::*
protected:
    void input_irl_num();
    void input_int_num();
    void input_str_num();
};

class InputTriangle : public InputAction {
public:
    void run() override; // TODO Implement InputTriangle::run
};

class InputCircle : public InputAction {
public:
    void run() override; // TODO Implement InputCircle::run
};

class InputRectangle : public InputAction {
public:
    void run() override; // TODO Implement InputRectangle::run
};

class InputConvexPolygon : public InputAction {
public:
    void run() override; // TODO Implement InputConvexPolygon::run
};

class App : public MenuList, Sort, DelByPerimeter, ShowFigures,
InputTriangle, InputRectangle, InputConvexPolygon, InputCircle {
public:
    void run() override; // TODO Implement App::run
private:
    MenuList _main_menu;
};

int main(int argc, char *argv[])
{
#ifdef DEBUG
    std::vector<Vector2> dots = {
        {1,0},
        {2,0},
    };
    try
    {
        PolyAngle poly_angle("Figur", dots);
    } catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
#endif



}

