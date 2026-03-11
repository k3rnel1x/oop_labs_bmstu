#include <iostream>
#include "finny_geometry.hpp"

class Data {
private:
    std::vector<Figure*> _appdata;
};

class Action : public Data {
public:
    Action()
    {
    };
    virtual void run() = 0;
};

class Input : public Action {
public:
    Input()
    {
    };
    void clear() { std::cout.clear(); }
    virtual void run() = 0;
};

class MenuItem : public Action {
public:
    MenuItem()
    {
    }

    MenuItem(std::string name) : Action()
    {
        if (name.empty())
            throw std::invalid_argument("Name must be non-emply.");

        _name = name;
    }
    MenuItem(std::string name, void (*action)()) : MenuItem(name)
    {
        if (!action)
            throw std::invalid_argument("Action must be non-null.");

        _action = action;
    }

    void show()
    {
        std::cout << _name;
    };

    void run()
    {
        if (_action == NULL)
            throw std::runtime_error("There is no action to run");
        _action();
    };

    void set_action(void (*action)())
    {
        _action = action;
    }
private:
    std::string _name;
    void (*_action)() = NULL;
};

class MenuList : public MenuItem {
typedef std::vector<MenuItem> MenuItemsList;
public:
    MenuList()
    {
    };
    MenuList(std::string name) :
    MenuItem(name)
    {
    }


void add_item(MenuItem menu_item)
    {
        _menu_items.push_back(menu_item);
    }

    void show()
    {
        int i = 0;
        for (; i < _menu_items.size(); i++)
        {
            std::cout << i + 1 << ". "; _menu_items[i].show();
            std::cout << std::endl;
        }
        // std::cout << i + 1 << ". Exit" << std::endl;
    }

    size_t get_len()
    {
        return _menu_items.size();
    }

    void run_num(int num)
    {
        if (!_validate_menu_num(num))
            throw std::invalid_argument("There is no this menu bla bla bla....");

        _menu_items[num-1].run();
    }

private:
    bool _validate_menu_num(int num) { return (0 < num) && (num <= _menu_items.size() + 1); }

    MenuItemsList _menu_items;
};

////

class Sort : public Action {
public:
    Sort()
    {
    };
    void run() override; // TODO Implement Sort::run
};

class DelByPerimeter : public Action {
public:
    void run() override; // TODO Implement DelByPerimeter::run
};

class ShowFigures : virtual public Input {
public:
    ShowFigures()
    {
    };
    void show();         // TODO Implement DelByPerimeter::show and show_perimeters
    void show_perimeters();
};

////
class InputAction : virtual public Input { // TODO Implement InputAction::*
public:
    InputAction()
    {
    };
protected:
    void input_irl_num();
    static int input_int_num(const std::string prompt) // TODO why static??
    {
        int num = 0;
        std::cout << prompt;
        std::cin >> num;
        return num;
    }
    void input_str_num();
};

class InputTriangle : public InputAction {
public:
    InputTriangle()
    {
    };
    void run() override; // TODO Implement InputTriangle::run
};

class InputCircle : public InputAction {
public:
    InputCircle()
    {
    };
    void run() override; // TODO Implement InputCircle::run
};

class InputRectangle : public InputAction {
public:
    InputRectangle()
    {
    };
    void run() override; // TODO Implement InputRectangle::run
};

class InputConvexPolygon : public InputAction {
public:
    InputConvexPolygon()
    {
    };
    void run() override; // TODO Implement InputConvexPolygon::run
};

class App : public MenuList, ShowFigures, InputAction
/*InputTriangle, InputRectangle, InputConvexPolygon, InputCircle DelByPerimeter Sort */ {
public:
    // App(MenuList main_menu) : Sort(), ShowFigures(), DelByPerimeter(), InputCircle(), InputRectangle(), InputTriangle(), InputConvexPolygon(),
    App(MenuList main_menu) :
        _main_menu(main_menu), _exit_item("Exit", this->_exit_action)
    {
        _main_menu.add_item(_exit_item);
    }

    void run()
    {
        int menu_num;
        do
        {
            clear();
            _main_menu.show();
            menu_num = input_int_num("What action u want to run? ");
            try {
                _main_menu.run_num(menu_num);
            } catch (std::invalid_argument& e) {
                clear();
                std::cout << e.what() << std::endl;
            } catch (std::exception& e) {
                break;
            }
        } while (true);
    }
private:
    MenuList _main_menu;
    MenuItem _exit_item;
    static void _exit_action()
    {
        throw std::exception();
    }
};

int main(int argc, char *argv[])
{

    MenuList menu_list;
    MenuItem menu_item("First");
    menu_list.add_item(menu_item);
    App app(menu_list);
    app.run();
}

