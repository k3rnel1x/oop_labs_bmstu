cmake_minimum_required(VERSION 4.2)
project(oop_labs_bmstu)

set(CMAKE_CXX_STANDARD 14)

include_directories(lab1)

add_executable(oop_labs_bmstu
        lab1/geomerty.hpp
        lab1/geometry.cpp
        lab1/geometrytoolkit.cpp
        lab1/geometrytoolkit.hpp
        lab1/main.cpp)
