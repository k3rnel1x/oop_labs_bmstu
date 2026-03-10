cmake_minimum_required(VERSION 4.2)
project(oop_labs_bmstu)

set(CMAKE_CXX_STANDARD 11)

include_directories(lab1)

link_libraries(stdc++)

add_executable(oop_labs_bmstu
        lab1/main.cpp
        lab1/finny_geometry.h
)
