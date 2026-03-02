#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>

using std::vector;
using std::string;

#define MAIN_MENU_PROMPT "Select:"

typedef enum action_res {
    LOOP_EXIT=-1, // loop exit
    SUCCESS=0,
    ERROR=1,
} ACTION_RES;

typedef enum menu_actions {
    ADD_GEOMETRY=1,
    SHOW_GEOMETRY_PARAM,
    SHOW_GEOMETRY_P,
    SHOW_SUM_P,
    SORT_BY_P,
    DEL_GEOMETRY,
    DEL_GEOMETRY_P
} MENU_ACTIONS;

typedef struct AppData {
    vector<std::unique_ptr<Geometry*>> geos,
} AppData;

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
    
    void getStrMenu    (const string prompt);
    void getRealNumMenu(const string prompt);
    int  getMenuChoice (const string prompt, MENU_ACTIONS first, MENU_ACTIONS last);

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