//
// Created by k3rnel1x on 07.03.2026.
//

#include "menu.h"
#include <exception>
#include <vector>
#include <iostream>
#include <string>

class Exception : public std::exception {
private:
    std::string ex;
public:
    Exception(const std::string ex) { this->ex = ex; }
    const char* what() const noexcept override {
        return this->ex.c_str();
    };
};


void Menu::print()
{
    clear();
    using std::cout;
    using std::endl;
    for (int i = 0; i < items.size(); i++)
        cout << i << ". " << items[i]->getName() << endl;
}

int Menu::get_menu_num(std::string prompt)
{
    int item;
    // Print prompt
    std::cout << prompt;
    std::cin >> item;
    return item;
}

void Menu::validate_num(int num)
{
    if ( !(1 <= num && num <= items.size()) )
        throw Exception("Menu index out of range");
}

void Menu::set_input_prompt(std::string input_prompt)
{
    this->input_prompt = input_prompt;
}

void Menu::exec()
{
    do
    {
        print();
        int num;
        clear();

        try {
            num = get_menu_num(input_prompt);
            validate_num(num);
        } catch (std::exception& e) {
            clear();
            std::cout << e.what() << std::endl;
        }

        try{
            items.at(num)->exec();
        } catch (std::exception& e) {
            break;
        }
    } while (true);
}
