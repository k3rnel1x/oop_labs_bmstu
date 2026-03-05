#pragma once
#include "config.hpp"


class GeometryToolKit
{
private:
    AppData* data;

    /* Сonstants */
    // static const int minMenu = 1;
    // static const int maxMenu = 7;
    
    /* IO */
    // TODO implement IO
    void clearConsole();
    void showMainMenu();
    
    void getStrMenu         (const string prompt);
    void getRealNumMenu     (const string prompt);
    int  getValidMenuChoice ();

    /* Menu Actions */
    // TODO implement Menu Actions
    ACTION_RES addGeo();
    ACTION_RES showGeoParametrs();
    ACTION_RES showGeoPerimeters();
    ACTION_RES showGeoSumPerimeters();
    ACTION_RES sortGeoByGrowPerimeters();
    ACTION_RES delGeo();
    ACTION_RES delGeoByBiggerPerimeter();

    /* Utils */
    // TODO implement showError
    void showError(ACTION_RES err);

public:
    GeometryToolKit(/* args */);
    ~GeometryToolKit();

    int exec();
};