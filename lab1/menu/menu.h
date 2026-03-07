//
// Created by k3rnel1x on 07.03.2026.
//

#ifndef MENU_H
#define MENU_H
#include <exception>
#include <vector>
#include <iostream>
#include <string>
#include "geometry.hpp"
#include "base/base.h"

class Menu : public Base {
private:
    std::vector<Base*> items;
    std::string input_prompt = "Select menu: ";

protected:
    void print();
    void validate_num(int item);
    int  get_menu_num(std::string prompt);

public:
    Menu(const std::string name, const std::vector<Base*> items) : Base(name) { this->items = items; };
    void set_input_prompt(std::string prompt = "Select menu: ");
    void exec() override;
};

#endif //MENU_H
