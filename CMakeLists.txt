cmake_minimum_required(VERSION 4.2)
project(lab2)

set(CMAKE_CXX_STANDARD 14)
# run main
set(SOURCES
		lab2/list.h
#		lab2/main.cpp
		lab2/tests.cpp
#		lab2/list.cpp
#		lab2/iterator.cpp
)
link_libraries(stdc++ m)
#add_executable(main lab2/main.cpp lab2/mylist.h)

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main

add_executable(lab2_tests ${SOURCES})
target_link_libraries(lab2_tests PRIVATE Catch2::Catch2WithMain)

#add_test(NAME lab2_memtest
#		COMMAND valgrind
#		--error-exitcode=1
#		--tool=memcheck
#		--leak-check=full
#		--errors-for-leak-kinds=definite
#		--show-leak-kinds=definite lab2_tests
#		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})