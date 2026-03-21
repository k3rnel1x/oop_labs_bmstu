//
// Created by k3rnel1x on 17.03.2026.
//

#include "libmenu.h"

// ******************* Menu item ********************* //

void MenuItem::clear()
{
    std::cout << "\033[2J\033[1;1H";
    // std::cout << std::fflush;
}
void MenuItem::clear_cin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

int MenuItem::input_int_num(const std::string prompt)
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

std::string MenuItem::input_str(const std::string prompt)
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

Vector2 MenuItem::input_vector(const std::string prompt)
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

double MenuItem::input_real_num(const std::string prompt)
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

void MenuItem::wait_for_user()
{
    clear_cin();
	while (!std::cin.peek());
}


// ******************* Main menu actions ******************* //

void Show::run()
{
    clear();
    if (_data->_appdata.empty())
        std::cout << "No figures :(" << std::endl;
    else
        for (int i = 0; i < _data->_appdata.size(); i++)
        {
            std::cout << i + 1 << ". Name:|" << _data->_appdata[i]->get_name() << "|"  << std::endl;
        }
    wait_for_user();
};

void ShowPerimeters::run()
{
    clear();
    if (_data->_appdata.empty())
        std::cout << "No figures :(" << std::endl;
    else
        for (int i = 0; i < _data->_appdata.size(); i++)
        {
            std::cout << i + 1 << ". Name:|" << _data->_appdata[i]->get_name()
                      << "| Perimeter:|" << _data->_appdata[i]->get_perimeter() << "|" << std::endl;
        }
    wait_for_user();
};

void ShowSum::run()
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

void Sort::run()
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

void DelByNum::run()
{
    clear();
    if (_data->_appdata.empty())
        std::cout << "No figures :(" << std::endl;
    else {
        int index = 0;
        do {

            index = input_int_num("Input number to delete:") - 1;
            if (0 < index || index >= _data->_appdata.size())
			{
				std::cout << "there is no menu element with this number" << std::endl;
                wait_for_user();
				return;
			}
			break;
        } while (true);
        // sleep(10);
        std::string name = _data->_appdata[index]->get_name();
        _data->_appdata.erase(_data->_appdata.begin() + index);
        clear();
        std::cout << "Deleted " << name << std::endl;
    }

    wait_for_user();
};

void DelByPerimeter::run()
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
				return;
            }
        } while (true);

        std::vector<Figure*>& figures = _data->_appdata;
        for (int i = 0; i < figures.size(); i++)
        {
            if (figures[i]->get_perimeter() > maximum_perimeter)
            {
                std::cout << "Deleted " << figures[i]->get_name() << std::endl;
                figures.erase(figures.begin() + i);
				i--;
            };
        }
        std::cout << "Deletion comlete." << std::endl;
    }
    wait_for_user();
};
