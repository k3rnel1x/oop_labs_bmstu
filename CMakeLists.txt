cmake_minimum_required(VERSION 4.2)
project(lab1)

set(CMAKE_CXX_STANDARD 11)

include_directories(lab1)

link_libraries(stdc++ m)

add_executable(lab1
        lab1/main.cpp
        lab1/finny_geometry.hpp
)

add_custom_target(
	run
	COMMAND ./lab1
	DEPENDS lab1
)
