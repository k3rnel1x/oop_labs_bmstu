#include <exception>
#include <vector>
#include <iostream>
#include <string>

#include "menu/menu.h"
#include "items/item.h"

int main()
{
    std::vector<Base*> add_menu_items;

    std::vector<Base*> main_menu_items;
    main_menu_items[0] = new Menu("Add menu", add_menu_items);
    main_menu_items[1] = new Item("Show geometry");

    Menu main("Main menu", main_menu_items);
    main.set_input_prompt("Sel item: ");
    main.exec();

    delete main_menu_items[0];
    delete main_menu_items[1];
    return 0;
}
