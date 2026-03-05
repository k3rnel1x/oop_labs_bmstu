#ifndef CONFIG_HPP

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "geomerty.hpp"

using std::vector;
using std::string;
using std::unique_ptr;

typedef enum menu_actions {
    ADD_GEOMETRY=1,
    SHOW_GEOMETRY_PARAM,
    SHOW_GEOMETRY_P,
    SHOW_SUM_P,
    SORT_BY_P,
    DEL_GEOMETRY,
    DEL_GEOMETRY_P
} MENU_ACTIONS;

typedef enum action_res {
    LOOP_EXIT=-1, 
    SUCCESS=0,
    ERROR=1,
} ACTION_RES;

#define MAIN_MENU_PROMPT  "Select:"
#define START_MENU_ACTION ADD_GEOMETRY
#define END_MENU_ACTION   DEL_GEOMETRY_P

typedef struct AppData {
    vector<unique_ptr<Geometry*>> geos;
} AppData;

#endif