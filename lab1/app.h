//
// Created by k3rnel1x on 17.03.2026.
//

#ifndef APP_H
#define APP_H
#include "addfiguremenu.h"

class App {
public:
    void run()
    {
        Data data;
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
};

#endif //APP_H
