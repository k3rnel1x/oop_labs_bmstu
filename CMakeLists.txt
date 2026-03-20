cmake_minimum_required(VERSION 4.2)
project(oop_labs_bmstu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
link_libraries(stdc++)

add_executable(oop_labs_bmstu
        lab2/mylist.cpp
        lab2/mylist.h
        lab2/main.cpp)

add_custom_target(run
		./oop_labs_bmstu
)
