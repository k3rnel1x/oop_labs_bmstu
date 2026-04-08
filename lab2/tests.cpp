//
// Created by k3rnel1x on 21.03.2026.
//
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "list.h"

// TEST_CASE("Test constructors")
// {
//     my::list<double> dlist = {1.3, -1, 1., 0};
//     SECTION("Test operator[]:")
//     {
//         GIVEN("list, inited with double nums: 1.3, -1, 1., 0")
//         {
//             REQUIRE(dlist[0] == 1.3);
//             REQUIRE(dlist[1] == -1);
//             REQUIRE(dlist[2] == 1.);
//             REQUIRE(dlist[3] == 0);
//         }
//     }
//
//     SECTION("list_copy[0..3] must show 1.3, -1, 1., 0")
//     {
//         my::list<double> list_copy{dlist};
//         REQUIRE(list_copy[0] == 1.3);
//         REQUIRE(list_copy[1] == -1);
//         REQUIRE(list_copy[2] == 1.);
//         REQUIRE(list_copy[3] == 0);
//     }
// }

TEST_CASE("Test constructors")
{
    SECTION("list()")
    {
        GIVEN("my::list<double> lst;")
        {
            my::list<double> lst;

            REQUIRE_THROWS_AS(lst[0], std::invalid_argument);
            REQUIRE(lst.get_len() == 0);
        }
    }

    SECTION("list(std::initializer_list<T> lst)")
    {
        GIVEN("my::list<double> lst = {1.3, -1, 1., 0};")
        {
            my::list<double> lst = {1.3, -1, 1., 0};

            REQUIRE_THROWS_AS(lst[-1], std::invalid_argument);
            REQUIRE(lst[0] == 1.3);
            REQUIRE(lst[1] == -1.0);
            REQUIRE(lst[2] == 1.);
            REQUIRE(lst[3] == 0);
            REQUIRE_THROWS_AS(lst[4], std::invalid_argument);
        }
    }

    SECTION("list(const list& lst)")
    {
        GIVEN("my::list<double> lst = {1.3, -1, 1., 0};\nmy::list<double> lst_copy(lst);")
        {
            my::list<double> lst = {1.3, -1, 1., 0};
            my::list<double> lst_copy(lst);

            REQUIRE_THROWS_AS(lst_copy[-1], std::invalid_argument);
            REQUIRE(lst_copy[0] == 1.3);
            REQUIRE(lst_copy[1] == -1);
            REQUIRE(lst_copy[2] == 1.);
            REQUIRE(lst_copy[3] == 0);
            REQUIRE_THROWS_AS(lst_copy[4], std::invalid_argument);
        }
    }

    SECTION("list(list&& lst)")
    {
        GIVEN("my::list<double> lst(my::list<double>{1.3, -1, 1., 0});")
        {
            my::list<double> lst(my::list<double>{1.3, -1, 1., 0});

            REQUIRE_THROWS_AS(lst[-1], std::invalid_argument);
            REQUIRE(lst[0] == 1.3);
            REQUIRE(lst[1] == -1);
            REQUIRE(lst[2] == 1.);
            REQUIRE(lst[3] == 0);
            REQUIRE_THROWS_AS(lst[4], std::invalid_argument);
        }
    }

    SECTION("list(list&& lst)")
    {
        GIVEN("my::list<double> tmp_list = {1.3, -1, 1., 0};  my::list<double> lst(std::move(tmp_list));")
        {
            my::list<double> tmp_list = {1.3, -1, 1., 0};
            my::list<double> lst(std::move(tmp_list));

            REQUIRE_THROWS_AS(lst[-1], std::invalid_argument);
            REQUIRE(lst[0] == 1.3);
            REQUIRE(lst[1] == -1);
            REQUIRE(lst[2] == 1.);
            REQUIRE(lst[3] == 0);
            REQUIRE_THROWS_AS(lst[4], std::invalid_argument);

            REQUIRE_THROWS_AS(tmp_list[0], std::exception);
            REQUIRE(tmp_list.get_len() == 0);
        }
    }
}

TEST_CASE("Test methods")
{
    SECTION("Getters")
    {
        GIVEN("my::list<double> lst;")
        {
            my::list<double> lst;
            REQUIRE(lst.get_len() == 0);

            REQUIRE(lst.indexof(-1.4) == -1);
            REQUIRE_THROWS_AS(lst.at(-1),     std::invalid_argument);

            REQUIRE_THROWS_AS(lst.get(-1),    std::invalid_argument);
        }

        GIVEN("my::list<double> lst = {1.3, 0., 1, 4444.2};")
        {
            my::list<double> lst = {1.3, 0., 1.0, 4444.2};
            REQUIRE(lst.get_len() == 4);

            REQUIRE(lst.indexof(1.3) == 0);
            REQUIRE(lst.indexof(0.0) == 1);
            REQUIRE(lst.indexof(1.)  == 2);
            REQUIRE(lst.indexof(4944.2) == -1);

            REQUIRE(lst.at(0) == 1.3);
            REQUIRE(lst.at(3) == 4444.2);

            REQUIRE(lst.get(0) == 1.3);
            REQUIRE(lst.get(3) == 4444.2);
        }

        GIVEN("my::list<double> lst = {1.3, 0., 1, 4444.2};\ndouble* arr = lst.to_array();")
        {
            my::list<double> lst = {1.3, 0., 1, 4444.2};
            double* arr = lst.to_array();
            REQUIRE(arr[0] == lst[0]);
            REQUIRE(arr[1] == lst[1]);
            REQUIRE(arr[2] == lst[2]);
            REQUIRE(arr[3] == lst[3]);

            WHEN("arr[0] = 14.2;")
            {
                arr[0] = 14.2;
                REQUIRE(arr[0] != lst[0]);
            }
        }
    }

    SECTION("Setters")
    {
        GIVEN("my::list<double> lst;\ndouble arr[5] = {89123.0, 23., 1, -123123};\n")
        {
            my::list<double> lst;
            double arr[5] = {89123.0, 23., 1, -123123};
            WHEN("lst.add(13.2);")
            {
                lst.add(13.2);
                REQUIRE(lst[0] == 13.2);
            }

            WHEN("lst.add(13.2);\nlst.add_range(arr, 5);")
            {
                lst.add(13.2);
                lst.add_range(arr, 5);
                REQUIRE(lst[0] == 13.2);
                REQUIRE(lst[1] == 89123.0);
                REQUIRE(lst[2] == 23.);
                REQUIRE(lst[3] == 1.0);
                REQUIRE(lst[4] == -123123.0);
                REQUIRE(lst[5] == 0.0);
            }
        }
    }
}

// SCENARIO("List initsialization")
// {
//     struct Vector2 {
//         int weight;
//         int height;
//     };
//     my::list<Vector2> mylist;
// }
//
// SCENARIO("Create list by initializer_list and check operator[] / test operator[]")
// {
//     GIVEN("A dlist of double: 1.3, -1, 1., 0")
//     {
//         my::list<double> dlist = {1.3, -1, 1., 0};
//         std::cout << "1: dlist.get_len() = " << dlist.get_len() << std::endl;
//         WHEN("dlist[0..3] must show 1.3, -1, 1., 0")
//         {
//             REQUIRE(dlist[0] == 1.3);
//             REQUIRE(dlist[1] == -1);
//             REQUIRE(dlist[2] == 1.);
//             REQUIRE(dlist[3] == 0);
//         }
//     }
// }
//
// SCENARIO("Copy list to another")
// {
//     GIVEN("my::list<double> dlist = {1.3, -1, 1., 0};\nmy::list<double> dlist_copy{dlist};")
//     {
//         my::list<double> dlist = {1.3, -1, 1., 0};
//         my::list<double> dlist_copy{dlist};
//         REQUIRE(dlist_copy.get_len() == 4);
//         REQUIRE(dlist.get_len() == 4);
//         REQUIRE(dlist_copy[0] == 1.3);
//         REQUIRE(dlist_copy[1] == -1);
//         REQUIRE(dlist_copy[2] == 1.);
//         REQUIRE(dlist_copy[3] == 0.0);
//     }
// }
//
// SCENARIO("Move list to another")
// {
//     GIVEN("A dlist_move, created by tmp-object, that inited with double numbers: 1.3, -1, 1., 0")
//     {
//         my::list<double> dlist_move{my::list<double>{1.3, -1, 1., 0}};
//         WHEN("dlist_move[0..3] must show 1.3, -1, 1., 0")
//         {
//             REQUIRE(dlist_move[0] == 1.3);
//             REQUIRE(dlist_move[1] == -1);
//             REQUIRE(dlist_move[2] == 1.);
//             REQUIRE(dlist_move[3] == 0);
//         }
//     }
// }
//
// SCENARIO("Creating empty list")
// {
//     GIVEN("A list1 of ints: 1 3 5 9")
//     {
//         my::list<int> list1;
//         list1.add(1);
//         list1.add(3);
//         list1.add(5);
//         list1.add(9);
//         WHEN("Init list2 with list1")
//         {
//             my::list<int> list2(list1);
//             REQUIRE( list2.get_len() == 4 );
//             REQUIRE( list2[0] == 1 );
//             REQUIRE( list2[1] == 3 );
//             REQUIRE( list2[2] == 5 );
//             REQUIRE( list2[3] == 9 );
//         }
//     }
// }