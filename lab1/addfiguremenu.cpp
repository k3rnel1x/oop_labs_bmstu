//
// Created by k3rnel1x on 17.03.2026.
//

#include "addfiguremenu.h"


// ********************** Menu actions ********************** //

void AddCircle::run()
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

void AddRectangle::run()
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

void AddTriangle::run()
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

void AddPolyAngle::run()
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
