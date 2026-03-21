//
// Created by k3rnel1x on 17.03.2026.
//

#ifndef LIBMENU_H
#define LIBMENU_H

#include <cstddef>
#include <exception>
#include <unistd.h>
#include <iostream>
#include "finny_geometry.hpp"
#include <cstdio>
#include <algorithm>
#include <climits>
#include <limits>
#define EPS 1e-6
class Data {
public:
    std::vector<Figure*> _appdata;
    ~Data()
    {
        if (!_appdata.empty())
            for (int i = 0; i < _appdata.size(); i++)
                free(_appdata[i]);
    }
};

class Action {
public:
    virtual void run() = 0;
};


class MenuItem : public Action {
public:
    void show()
    {
        std::cout << _name;
    }

protected:
    // utils
    void clear();

    void clear_cin();

    int input_int_num(std::string prompt);

    std::string input_str(std::string prompt);

    Vector2 input_vector(std::string prompt);

    double input_real_num(std::string prompt);

    void wait_for_user();


    MenuItem()
    {
    };

    ~MenuItem()
    {
    };

    MenuItem(const std::string name)
    {
        if (name.empty())
            throw std::invalid_argument("Name must be non-emply.");

        _name = name;
    }

    MenuItem(const std::string name, Data* data) : Action()
    {
        if (name.empty())
            throw std::invalid_argument("Name must be non-emply.");

        if (!data)
            throw std::invalid_argument("Data is null");

        _data = data;
        _name = name;
    }

    Data* _data;
private:
    std::string _name;
};

class MenuComposite : public MenuItem {
typedef std::vector<MenuItem*> MenuItemsList;
public:
    MenuComposite(std::string name) : MenuItem(name)
    {
    }


    void add_item(MenuItem* menu_item)
    {
        _menu_items.push_back(menu_item);
    }

    void show()
    {
        int i = 0;
        for (; i < _menu_items.size(); i++)
        {
            std::cout << i + 1 << ". "; _menu_items[i]->show();
            std::cout << std::endl;
        }
        std::cout << i + 1 << ". Exit" << std::endl;
    }

    size_t get_len()
    {
        return _menu_items.size();
    }

    void run_num(int num)
    {
        _menu_items[num-1]->run();
		clear_cin();
    }

    void run() override
    {
        int num;
        do
        {
            clear();
            // clear_cin();
            this->show();
			try {
            	num = input_int_num("Input menu num:");
			} catch(std::exception& e) {
				break;
			}

            if (num == _menu_items.size() + 1)
                break;

            if (_validate_menu_num(num))
                this->run_num(num);
            else
            {
                clear();
                std::cout << "There is no this menu bla bla bla...." << std::endl;
                wait_for_user();
            }

        } while (true);
    }
protected:



private:
    bool _validate_menu_num(int num)
    {
        return (0 < num) && (num <= _menu_items.size() + 1);
    }

    MenuItemsList _menu_items;
};


class Show : public MenuItem {
public:
    Show(Data* data) : MenuItem("Show", data)
    {
    }

    void run() override;

protected:
    void clear()
    {
        std::cout << "\033[2J\033[1;1H";
        std::cout << std::flush;
    }
};

class ShowPerimeters : public MenuItem {
public:
    ShowPerimeters(Data* data) : MenuItem("Show perimeters", data)
    {
    }

    void run() override;
};

class ShowSum : public MenuItem {
public:
    ShowSum(Data* data) : MenuItem("Show sum of perimeters", data)
    {
    }

    void run() override;
};

class Sort : public MenuItem {
public:
    Sort(Data* data) : MenuItem("Sort perimeters", data)
    {
    }

    void run() override;
private:
    static bool perimeter_cmp(Figure* a, Figure* b)
    {
        return a->get_perimeter() < b->get_perimeter();
    }
};

class DelByNum : public MenuItem {
public:
    DelByNum(Data* data) : MenuItem("Delete by number", data)
    {
    }

    void run() override;
private:
    static bool perimeter_cmp(Figure* a, Figure* b)
    {
        return a->get_perimeter() < b->get_perimeter();
    }
};

class DelByPerimeter : public MenuItem {
public:
    DelByPerimeter(Data* data) : MenuItem("Delete by perimeter", data)
    {
    }

    void run() override;

private:
    static bool perimeter_cmp(Figure* a, Figure* b)
    {
        return a->get_perimeter() < b->get_perimeter();
    }
};



#endif //LIBMENU_H
