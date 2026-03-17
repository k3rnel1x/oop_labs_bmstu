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

    void run() override
    {
        do{
            std::string name;
            Vector2 center;
            double  radius;
            try {
                name =   input_str("Input name:");
                center = input_vector("Input center:");
                radius = input_real_num("Input radius:");
            } catch (std::exception& e) {
                return;
            }

            try {
                _data->_appdata.push_back(new Circle(name, center, radius));
            } catch(std::exception& e){
                clear();
                std::cout << e.what() << std::endl;
                std::cout << "here we go again..." << std::endl;
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
                std::cout << "here we go again..." << std::endl;
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
                std::cout << "here we go again..." << std::endl;
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
            int points_count;
            std::string name;
            try {
                name = input_str("Input name:");
                points_count = input_int_num("Input count of angles:");
            } catch(std::exception& e) {
                break;
            }

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
                std::cout << "here we go again..." << std::endl;
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
            int index = 0;
            do {

                index = input_int_num("Input number to delete:") - 1;
                if (0 < index && index < _data->_appdata.size())
                    break;
                else
                {
                    std::cout << "Input error" << std::endl;
                    wait_for_user();
                }
            } while (true);
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
            double maximum_perimeter;
            do
            {
                try {
                    maximum_perimeter = input_real_num("Input maximum perimeter:");
                } catch (std::exception& e) {
                    return;
                }
                if (maximum_perimeter > 0.0)
                {
                    break;
                } else
                {
                    std::cout << "Error: perimeter must be more than 0" << std::endl;
                    wait_for_user();
                }
            } while (true);

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


#endif //ADDFIGUREMENU_H
