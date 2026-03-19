cmake_minimum_required(VERSION 4.2)
project(oop_labs_bmstu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
link_libraries(stdc++)

add_executable(oop_labs_bmstu
        iterator.cpp
        iterator.h
        mylist.cpp
        mylist.h
        main.cpp)
