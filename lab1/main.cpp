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
        // std::cin.clear();
        // std::cin.ignore(LONG_MAX,'\n');
    }
	void clear_cin()
    {
        // std::cin.sync();
        // std::cin.clear();
        // std::cin.ignore(LONG_MAX,'\n');
		int c;
		if(!std::cin.eof())
        	while ((c = getchar()) != '\n' && c != EOF);
    }

    int input_int_num(const std::string prompt)
    {
        int num = 0;
        std::string buff;
        do
        {
			std::cout << prompt;
           	if(!std::getline(std::cin, buff) || buff.empty()){
                std::cout << "Input error" << std::endl;
				clear_cin();
                wait_for_user();
                continue;
            } else {
				num = std::stoi(buff);
			}
            break; 
        } while (true);
        return num;
    }

    unsigned long input_uint_num(const std::string prompt) // TODO if user inputs -1 or 0 -> err
    {
		unsigned long num = 0;
        std::string buff;
        do
        {
			std::cout << prompt;
           	if(!std::getline(std::cin, buff) || buff.empty()){
                std::cout << "Input error" << std::endl;

                wait_for_user();
                continue;
            } else {
				try {
					num = std::stoul(buff);
				} catch(std::exception& e) {
					std::cout << "Input error" << std::endl;

	                // wait_for_user();
					clear_cin();
	                continue;
				}
			}
            break; 
        } while (true);

		std::cout << "num = " << num;
		std::cout << fflush;
		sleep(5);
        return num; 
    }

    std::string input_str(const std::string prompt)
    {
        size_t num = 0;
        std::string str;
        do
        {
            clear_cin();
            std::cout << prompt;
            getline(std::cin, str);

            if(!str[0] || std::cin.fail() || (!std::cin.eof() && std::cin.peek() != '\n')){
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
        Vector2 v;
        std::cout << prompt;
		if(std::cin.eof())
			throw std::exception();

		std::cin >> v.x;
		std::cin >> v.y;

        return v;
    }

    double input_real_num(const std::string prompt)
    {
        double num = 0;
        std::cout << prompt;
		if(std::cin.eof())
			throw std::exception();

		std::cin >> num;
        return num;
    }

    void wait_for_user()
    {
        // clear_cin();
		if(!std::cin.eof())
	        while (!std::cin.peek());

        // std::cin.ignore(LONG_MAX,'\n');
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
		// std::cout << _name << std::endl;
		// clear();
		// clear_cin();
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

class AddCircle : public MenuItem {

public:
    AddCircle(Data* data) : MenuItem("Add circle", data)
    {
    }

    void run() override
    {
        do{
            std::string name = input_str("Input name:");
            Vector2 center = input_vector("Input center:");
            double  radius = input_real_num("Input radius:");

            try {
                _data->_appdata.push_back(new Circle(name, center, radius));
            } catch(std::exception& e){
                clear();
                std::cout << e.what() << std::endl;
                continue;
            }

            break;
        } while(true);
    };
};


class AddRectangle : public MenuItem {
public:
    AddRectangle(Data* data) : MenuItem("Add rectangle", data)
    {
    }

    void run() override
    {
        do{
            std::string name = input_str("Input name:");
            Vector2 left_corner = input_vector("Input left corner:");
            Vector2 right_corner = input_vector("Input right corner:");

            try {
                _data->_appdata.push_back(new Rectangle(name, left_corner, right_corner));
            } catch(std::exception& e){
                clear();
                std::cout << e.what() << std::endl;
                continue;
            }

            break;
        } while(true);
    };
};

class AddTriangle : public MenuItem {
public:
    AddTriangle(Data* data) : MenuItem("Add triangle", data)
    {
    }

    void run() override
    {
        do{
            std::string name = input_str("Input name:");
            Vector2 a = input_vector("Input a:");
            Vector2 b = input_vector("Input b:");
            Vector2 c = input_vector("Input c:");

            try {
                _data->_appdata.push_back(new Triangle(name, a, b, c));
            } catch(std::exception& e){
                clear();
                std::cout << e.what() << std::endl;
                continue;
            }

            break;
        } while(true);
    };
};

class AddPolyAngle : public MenuItem {
public:
    AddPolyAngle(Data* data) : MenuItem("Add polyangle", data)
    {
    }

    void run() override
    {
        do{
            std::string name = input_str("Input name:");
            size_t points_count = input_uint_num("Input count of angles:");
            std::vector<Vector2> dots;
            for(int i = 0; i < points_count; i++)
            {
                Vector2 v = input_vector("Input angle:");
                dots.push_back(v);
            }


            try {
                _data->_appdata.push_back(new PolyAngle(name, dots));
            } catch(std::exception& e){
                clear();
                std::cout << e.what() << std::endl;
                continue;
            }

            break;
        } while(true);
    };
};

class Show : public MenuItem {
public:
    Show(Data* data) : MenuItem("Show", data)
    {
    }

    void run() override
    {
        clear();
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
        clear();
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
        clear();
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

class Sort : public MenuItem {
public:
    Sort(Data* data) : MenuItem("Sort perimeters", data)
    {
    }

    void run() override
    {
        clear();
        if (_data->_appdata.empty())
            std::cout << "No figures :(" << std::endl;
        else {
            std::vector<Figure*>& figures = _data->_appdata;

            std::sort(figures.begin(), figures.end(), perimeter_cmp);

            std::cout << "Sorted." << std::endl;
        }

        wait_for_user();
    };
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

    void run() override
    {
        clear();
        if (_data->_appdata.empty())
            std::cout << "No figures :(" << std::endl;
        else {
            unsigned long index = input_uint_num("Input number to delete:") - 1;
			// sleep(10);
            std::string name = _data->_appdata[index]->get_name();
            _data->_appdata.erase(_data->_appdata.begin() + index);
            clear();
            std::cout << "Deleted " << name << std::endl;
        }

        wait_for_user();
    };
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

    void run() override
    {
        clear();
        if (_data->_appdata.empty())
            std::cout << "No figures :(" << std::endl;
        else {
            double maximum_perimeter = input_real_num("Input maximum perimeter:");
            std::vector<Figure*>& figures = _data->_appdata;
            for (int i = 0; i < figures.size(); i++)
            {
                if (figures[i]->get_perimeter() > maximum_perimeter)
                {
                    std::cout << "Deleted " << figures[i]->get_name() << std::endl;
                    figures.erase(figures.begin() + i);
                }
            }
            std::cout << "Deletion comlete." << std::endl;
        }
        wait_for_user();
    };
private:
    static bool perimeter_cmp(Figure* a, Figure* b)
    {
        return a->get_perimeter() < b->get_perimeter();
    }
};

int main()
{
    /************************ Tests ************************/
    std::vector<Vector2> coords = {
        {2,3},
        {5,4},
        {3,2},
        {1,1},
        {1.5,2},
    };
    Data data = {._appdata = {
        new Triangle("4Tri", (Vector2){-1, 2}, (Vector2){3, 1}, (Vector2){9, 5}),
        new PolyAngle("1Poly", coords),
        new Circle("3Circ", (Vector2){0}, 2),
        new Rectangle("2Rect", (Vector2){-1, 2}, (Vector2){3, 1}),
    }};


    /************************ Construct main menu ************************/
    MenuList main_menu("Main");

    // Add figures
    AddCircle    circle(&data);
    AddRectangle rectangle(&data);
    AddTriangle  tritangle(&data);
    AddPolyAngle polyangle(&data);

    MenuList add_figures("Add figures");
    add_figures.add_item(&circle);
    add_figures.add_item(&rectangle);
    add_figures.add_item(&tritangle);
    add_figures.add_item(&polyangle);
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

    // Sort
    Sort sort(&data);
    main_menu.add_item(&sort);

    // Del by num
    DelByNum del_by_num(&data);
    main_menu.add_item(&del_by_num);

    // Del by perimeter
    DelByPerimeter del_by_perimeter(&data);
    main_menu.add_item(&del_by_perimeter);

    /************************ Run main menu ************************/
    main_menu.run();
}

