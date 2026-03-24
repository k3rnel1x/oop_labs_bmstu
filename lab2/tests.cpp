//
// Created by k3rnel1x on 21.03.2026.
//
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "mylist.h"

SCENARIO("Create empty list of int")
{
    my::mylist<int> mylist;
}

// TEST_CASE("Test list, inited with double nums: 1.3, -1, 1., 0")
TEST_CASE("Test list")
{
    my::mylist<double> dlist = {1.3, -1, 1., 0};
    SECTION("Test operator[]:")
    {
        GIVEN("list, inited with double nums: 1.3, -1, 1., 0")
        {
            REQUIRE(dlist[0] == 1.3);
            REQUIRE(dlist[1] == -1);
            REQUIRE(dlist[2] == 1.);
            REQUIRE(dlist[3] == 0);
        }
    }

    SECTION("list_copy[0..3] must show 1.3, -1, 1., 0")
    {
        my::mylist<double> list_copy{dlist};
        REQUIRE(list_copy[0] == 1.3);
        REQUIRE(list_copy[1] == -1);
        REQUIRE(list_copy[2] == 1.);
        REQUIRE(list_copy[3] == 0);
    }
}

SCENARIO("List initsialization")
{
    struct Vector2 {
        int weight;
        int height;
    };
    my::mylist<Vector2> mylist;
}

SCENARIO("Create list by initializer_list and check operator[] / test operator[]")
{
    GIVEN("A dlist of double: 1.3, -1, 1., 0")
    {
        my::mylist<double> dlist = {1.3, -1, 1., 0};
        WHEN("dlist[0..3] must show 1.3, -1, 1., 0")
        {
            REQUIRE(dlist[0] == 1.3);
            REQUIRE(dlist[1] == -1);
            REQUIRE(dlist[2] == 1.);
            REQUIRE(dlist[3] == 0);
        }
    }
}

SCENARIO("Copy list to another")
{
    GIVEN("A dlist of double: 1.3, -1, 1., 0, copyed dlist_copy")
    {
        my::mylist<double> dlist = {1.3, -1, 1., 0};
        my::mylist<double> dlist_copy{dlist};
        WHEN("dlist_copy[0..3] must show 1.3, -1, 1., 0")
        {
            REQUIRE(dlist_copy[0] == 1.3);
            REQUIRE(dlist_copy[1] == -1);
            REQUIRE(dlist_copy[2] == 1.);
            REQUIRE(dlist_copy[3] == 0);
        }
    }
}

SCENARIO("Move list to another")
{
    GIVEN("A dlist_move, created by tmp-object, that inited with double numbers: 1.3, -1, 1., 0")
    {
        my::mylist<double> dlist_move{my::mylist<double>{1.3, -1, 1., 0}};
        WHEN("dlist_move[0..3] must show 1.3, -1, 1., 0")
        {
            REQUIRE(dlist_move[0] == 1.3);
            REQUIRE(dlist_move[1] == -1);
            REQUIRE(dlist_move[2] == 1.);
            REQUIRE(dlist_move[3] == 0);
        }
    }
}

SCENARIO("Creating empty list")
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