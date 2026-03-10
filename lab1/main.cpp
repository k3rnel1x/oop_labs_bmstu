#include <iostream>
#include "finny_geometry.h"

class Data {
private:
    std::vector<Figure*> _appdata;
};

int main(int argc, char *argv[])
{
#ifdef DEBUG
    std::vector<Vector2> dots = {
        {1,0},
        {2,0},
    };
    try
    {
        PolyAngle poly_angle("Figur", dots);
    } catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
#endif



}

