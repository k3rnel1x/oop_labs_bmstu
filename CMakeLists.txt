cmake_minimum_required(VERSION 4.2)
project(lab2)

set(CMAKE_CXX_STANDARD 14)
# run main
set(SOURCES
		lab2/mylist.h
		lab2/main.cpp
		lab2/mylist.cpp
)
link_libraries(stdc++ m)
#add_executable(main lab2/main.cpp lab2/mylist.h)

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main

add_executable(lab2_tests ${SOURCES})
target_link_libraries(lab2_tests PRIVATE Catch2::Catch2WithMain)
