cmake_minimum_required(VERSION 4.2)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
link_libraries(stdc++ m)
add_executable(lab2_tests
		lab2/mylist.h
		lab2/tests.cpp
)
target_link_libraries(lab2_tests PRIVATE Catch2::Catch2WithMain)