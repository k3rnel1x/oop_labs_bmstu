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
    };

protected:
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
    void clear()
    {
        std::cout << "\033[2J\033[1;1H";
        // std::cout << std::fflush;
    }
	void clear_cin()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    int input_int_num(const std::string prompt)
    {


        int num = 0;
        do
        {
            if (std::cin.eof())
                throw std::exception();

            std::cout << prompt;
            std::cin >> num;
            if (std::cin.fail() || std::cin.eof() || (!std::cin.eof() && std::cin.peek() != '\n'))
            {
                std::cout << "Input error" << std::endl;
                clear_cin();
                continue;
            }
            break;
        } while (true);
        return num;
    }

    std::string input_str(const std::string prompt)
    {
        size_t num = 0;
        std::string str;
        do
        {
            if (std::cin.eof())
                throw std::exception();


            clear_cin();
            std::cout << prompt;

            if(!getline(std::cin, str, '\n') || !str[0] || std::cin.fail()){
                std::cout << "Input error" << std::endl;
                wait_for_user();
                continue;
            }
            break;
        } while (true);

        return str;
    }

    Vector2 input_vector(const std::string prompt)
    {
        if(std::cin.eof())
            throw std::exception();

        Vector2 v;
        do
        {
            if (std::cin.eof())
                throw std::exception();

            std::cout << prompt;
            std::cin >> v.x >> v.y;
            if (std::cin.fail() || std::cin.eof() || (!std::cin.eof() && std::cin.peek() != '\n'))
            {
                std::cout << "Input error" << std::endl;
                clear_cin();
                continue;
            }
            break;
        } while (true);
        return v;
    }

    double input_real_num(const std::string prompt)
    {
        double num = 0;
        do
        {
            if (std::cin.eof())
                throw std::exception();

            std::cout << prompt;
            std::cin >> num;
            if (std::cin.fail() || std::cin.eof() || (!std::cin.eof() && std::cin.peek() != '\n'))
            {
                std::cout << "Input error" << std::endl;
                clear_cin();
                continue;
            }
            break;
        } while (true);
        return num;
    }

    void wait_for_user()
    {
        clear_cin();
	    while (!std::cin.peek());
    }

    Data* _data;
private:
    std::string _name;
};

class MenuList : public MenuItem {
typedef std::vector<MenuItem*> MenuItemsList;
public:
    MenuList(std::string name) : MenuItem(name)
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



#endif //LIBMENU_H
