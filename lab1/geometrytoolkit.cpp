#include "geometrytoolkit.hpp"
// TODO split??

ACTION_RES GeometryToolKit::addGeo()
{
    // TODO addGeo
}

ACTION_RES GeometryToolKit::showGeoParametrs()
{
    // TODO showGeoParametrs
}

ACTION_RES GeometryToolKit::showGeoPerimeters()
{
    // TODO showGeoPerimeters
}

ACTION_RES GeometryToolKit::showGeoSumPerimeters()
{
    // TODO showGeoSumPerimeters
}

ACTION_RES GeometryToolKit::sortGeoByGrowPerimeters()
{
    // TODO sortGeoByGrowPerimeters
}

ACTION_RES GeometryToolKit::delGeo()
{
    // TODO delGeo
}

ACTION_RES GeometryToolKit::delGeoByBiggerPerimeter()
{
    // TODO delGeoByBiggerPerimeter
}

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