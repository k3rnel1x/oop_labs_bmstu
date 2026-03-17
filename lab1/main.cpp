#include "finny_geometry.hpp"
#include "libmenu/libmenu.h"
#include "app.h"

int main()
{
    // /************************ Tests ************************/
    // std::vector<Vector2> coords = {
    //     {2,3},
    //     {5,4},
    //     {3,2},
    //     {1,1},
    //     {1.5,2},
    // };
    // Data data = {._appdata = {
    //     new Triangle("4Tri", (Vector2){-1, 2}, (Vector2){3, 1}, (Vector2){9, 5}),
    //     new PolyAngle("1Poly", coords),
    //     new Circle("3Circ", (Vector2){0}, 2),
    //     new Rectangle("2Rect", (Vector2){-1, 2}, (Vector2){3, 1}),
    // }};

    App app;
    app.run();
    return 0;
}

