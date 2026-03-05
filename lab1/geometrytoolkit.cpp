#include "geometrytoolkit.hpp"
GeometryToolKit::GeometryToolKit()
{
    data = new AppData;
}

GeometryToolKit::~GeometryToolKit()
{
    delete data;
}

int GeometryToolKit::exec()
{
    int menuChoice = 0;
    ACTION_RES actionRes = SUCCESS;

    do {
        menuChoice = this->getValidMenuChoice();

        // run action
        switch (menuChoice)
        {
        case ADD_GEOMETRY:
            actionRes = this->addGeo();
            break;

        case SHOW_GEOMETRY_PARAM:
            actionRes = this->showGeoParametrs();
            break;

        case SHOW_GEOMETRY_P:
            actionRes = this->showGeoPerimeters();
            break;

         case SHOW_SUM_P:
            actionRes = this->showGeoSumPerimeters(); 
            break;

        case DEL_GEOMETRY:
            actionRes = this->delGeo();
            break;

        case DEL_GEOMETRY_P:
            actionRes = this->delGeoByBiggerPerimeter();
            break;    
        }   

        if(actionRes != SUCCESS && actionRes != LOOP_EXIT)
            this->showError(actionRes);

    } while(actionRes != LOOP_EXIT);

    return EXIT_SUCCESS;
}