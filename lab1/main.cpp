#include <iostream>
#include "finny_geometry.hpp"
#include <cstdio>

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
        // std::cout << "\033[2J\033[1;1H";
        // std::cout << std::flush;
    }

    void wait_for_user()
    {
        int is_user_ready = 0;
        do{
            is_user_ready = std::getchar();
        } while(!std::cin.eof() || is_user_ready != '\n');
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
    }

    void run() override
    {
        int num;
        do
        {
            // clear();
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
                std::cout << "There is no this menu bla bla bla...." << std::endl;

        } while (true);
    }
protected:

    int input_int_num(const std::string prompt)
    {
        int num = 0;
        std::cout << prompt;
		if(std::cin.eof())
			throw std::exception();
		
		char* line = (char*)malloc(100*sizeof(char));;
		std::cin.getline(line, 99);

		if(line[100-1] != 0)
		{
			printf("trigger\n");
			while(!std::cin.eof())
				std::cin.ignore();

			throw std::exception();
		}


		num = atoi(line);
        return num;
    }

private:
    bool _validate_menu_num(int num)
    {
        return (0 < num) && (num <= _menu_items.size() + 1);
    }

    MenuItemsList _menu_items;
};

class AddCircle : public MenuItem {
public:
    AddCircle(Data* data) : MenuItem("Add circle", data)
    {
    }

    void run() override
    {
        // Circle* cptr = new Circle("Name", (Vector2){0}, 2);
        // _data->_appdata.push_back(cptr);
    };
};


class Show : public MenuItem {
public:
    Show(Data* data) : MenuItem("Show", data)
    {
    }

    void run() override
    {
        // clear();
        if (_data->_appdata.empty())
            std::cout << "No figures :(" << std::endl;
        else
            for (int i = 0; i < _data->_appdata.size(); i++)
            {
                std::cout << i + 1 << ". " << _data->_appdata[i]->get_name() << std::endl;
            }
        wait_for_user();
    };

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

    void run() override
    {
        // clear();
        if (_data->_appdata.empty())
            std::cout << "No figures :(" << std::endl;
        else
            for (int i = 0; i < _data->_appdata.size(); i++)
            {
                std::cout << i + 1 << ". " << _data->_appdata[i]->get_name()
                          << " Perimeter:" << _data->_appdata[i]->get_perimeter() << std::endl;
            }
        wait_for_user();
    };

};

class ShowSum : public MenuItem {
public:
    ShowSum(Data* data) : MenuItem("Show sum of perimeters", data)
    {
    }

    void run() override
    {
        // clear();
        if (_data->_appdata.empty())
            std::cout << "No figures :(" << std::endl;
        else {
            double sum = 0;
            for (int i = 0; i < _data->_appdata.size(); i++)
                sum += _data->_appdata[i]->get_perimeter();

            std::cout << "All perimeters sum: " << sum << std::endl;
        }

        wait_for_user();
    };
};

int main()
{
    Data data;
    /* Construct main menu */
    MenuList main_menu("Main");
    // Add figures
    AddCircle circle(&data);
    MenuList add_figures("Add figures");
    add_figures.add_item(&circle);
    main_menu.add_item(&add_figures);

    // Show
    Show show(&data);
    main_menu.add_item(&show);

    // Show perimeters
    ShowPerimeters show_perimeters(&data);
    main_menu.add_item(&show_perimeters);

    // Show sum
    ShowSum show_sum(&data);
    main_menu.add_item(&show_sum);

    // // Sort
    // Sort sort(&data);
    // main_menu.add_item(&sort);
    //
    // // Del by num
    // DelByNum del_by_num(&data);
    // main_menu.add_item(&del_by_num);
    //
    // // Del by perimeter
    // DelByPerimeter del_by_perimeter(&data);
    // main_menu.add_item(&del_by_perimeter);

    main_menu.run();
}

