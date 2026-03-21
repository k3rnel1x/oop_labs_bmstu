//
// Created by k3rnel1x on 21.03.2026.
//
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "mylist.h"

SCENARIO("Copy constructor must copy list")
{
    GIVEN("A list1 of ints: 1 3 5 9")
    {
        my::mylist<int> list1;
        list1.add(1);
        list1.add(3);
        list1.add(5);
        list1.add(9);
        WHEN("Init list2 with list1")
        {
            my::mylist<int> list2(list1);
            REQUIRE( list2.get_len() == 4 );
            REQUIRE( list2[0] == 1 );
            REQUIRE( list2[1] == 3 );
            REQUIRE( list2[2] == 5 );
            REQUIRE( list2[3] == 9 );
        }
    }
}