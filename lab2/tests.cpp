//
// Created by k3rnel1x on 21.03.2026.
//
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "list.h"

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

    SECTION("list(std::initializer_list<T> lst), list(const list& lst)")
    {
        GIVEN("my::list<double> lst = {-6.7, -52., 69, .42};\nmy::list<double> lst_copy(lst);")
        {
            my::list<double> lst = {-6.7, -52., 69, .42};
            my::list<double> lst_copy(lst);

            REQUIRE_THROWS_AS(lst[-1], std::invalid_argument);
            REQUIRE(lst[0] == -6.7);
            REQUIRE(lst[1] == -52.);
            REQUIRE(lst[2] == 69);
            REQUIRE(lst[3] == 0.42);
            REQUIRE_THROWS_AS(lst[4], std::invalid_argument);

            REQUIRE_THROWS_AS(lst_copy[-1], std::invalid_argument);
            REQUIRE(lst_copy[0] == -6.7);
            REQUIRE(lst_copy[1] == -52.);
            REQUIRE(lst_copy[2] == 69);
            REQUIRE(lst_copy[3] == 0.42);
            REQUIRE_THROWS_AS(lst_copy[4], std::invalid_argument);
        }
    }

    SECTION("list(list&& lst)")
    {
        SECTION("r-value")
        {
            GIVEN("my::list<double> lst(my::list<double>{-6.7, -52., 69, .42});")
            {
                my::list<double> lst(my::list<double>{-6.7, -52., 69, .42});

                REQUIRE_THROWS_AS(lst[-1], std::invalid_argument);
                REQUIRE(lst[0] == -6.7);
                REQUIRE(lst[1] == -52.);
                REQUIRE(lst[2] == 69);
                REQUIRE(lst[3] == 0.42);
                REQUIRE_THROWS_AS(lst[4], std::invalid_argument);
            }
        }

        SECTION("std::move")
        {
            GIVEN("my::list<double> tmp_list = {{-6.7, -52., 69, .42};  my::list<double> lst(std::move(tmp_list));")
            {
                my::list<double> tmp_list = {-6.7, -52., 69, .42};
                my::list<double> lst(std::move(tmp_list));

                REQUIRE_THROWS_AS(lst[-1], std::invalid_argument);
                REQUIRE(lst[0] == -6.7);
                REQUIRE(lst[1] == -52.);
                REQUIRE(lst[2] == 69);
                REQUIRE(lst[3] == 0.42);
                REQUIRE_THROWS_AS(lst[4], std::invalid_argument);

                REQUIRE_THROWS_AS(tmp_list[0], std::exception);
                REQUIRE(tmp_list.get_len() == 0);
            }
        }
    }
}

TEST_CASE("Test methods")
{
    SECTION("Getters")
    {
        SECTION("at, indexof, get")
        {
            GIVEN("my::list<double> lst;")
            {
                my::list<double> lst;
                REQUIRE(lst.get_len() == 0);

                REQUIRE(lst.indexof(-1.4) == -1);
                REQUIRE_THROWS_AS(lst.at(-1),     std::invalid_argument);

                REQUIRE_THROWS_AS(lst.get(-1),    std::invalid_argument);
            }

            GIVEN("my::list<double> lst = {-6.7, -52., 69, .42};")
            {
                my::list<double> lst = {-6.7, -52., 69, .42};
                REQUIRE(lst.get_len() == 4);

                REQUIRE(lst.indexof(-6.7) == 0);
                REQUIRE(lst.indexof(-52.) == 1);
                REQUIRE(lst.indexof(69)  == 2);
                REQUIRE(lst.indexof(.42) == 3);
                REQUIRE(lst.indexof(.422) == -1);

                REQUIRE(lst.get(0) == -6.7);
                REQUIRE(lst.get(3) == .42);
            }
        }

        SECTION("to_array")
        {
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

        SECTION("unit")
        {
            GIVEN("my::list<double> lst = {67, 67, 6.7, 69};\nmy::list<double> list = {5.2, 4.2};")
            {
                my::list<double> lst  = {67, 67, 6.7, 69};
                my::list<double> list = {5.2, 4.2};
                WHEN("my::list<double> nlist = list.unit(lst);")
                {
                    my::list<double> nlist = lst.unit(list);
                    REQUIRE(nlist.get_len() == 6);
                    REQUIRE(nlist[0] == lst[0]);
                    REQUIRE(nlist[1] == lst[1]);
                    REQUIRE(nlist[2] == lst[2]);
                    REQUIRE(nlist[3] == lst[3]);
                    REQUIRE(nlist[4] == list[0]);
                    REQUIRE(nlist[5] == list[1]);
                }
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

TEST_CASE("Test operators")
{
    SECTION("operator=")
    {
        GIVEN("my::list<double> lst = {1.3, -1, 1., 0};")
        {
            my::list<double> lst = {1.3, -1, 1., 0};
            WHEN("trying to copy lst")
            {
                my::list<double> lst_copy;
                lst_copy = lst;
                REQUIRE_THROWS_AS(lst_copy[-1], std::invalid_argument);
                REQUIRE(lst_copy[0] == 1.3);
                REQUIRE(lst_copy[1] == -1.0);
                REQUIRE(lst_copy[2] == 1.);
                REQUIRE(lst_copy[3] == 0);
                REQUIRE_THROWS_AS(lst_copy[4], std::invalid_argument);
            }
        }
    }

    SECTION("operator==")
    {
        GIVEN("my::list<double> lst = {1.3, -1, 1., 0};\nmy::list<double> lst_copy = lst;\nmy::list<double> lst_not_copy = lst_copy; lst_not_copy.add(4.);")
        {
            my::list<double> lst = {1.3, -1, 1., 0};
            my::list<double> lst_copy = lst;
            my::list<double> lst_not_copy = lst_copy;
            lst_not_copy.add(4.);
            REQUIRE((lst_copy == lst) == true);
            REQUIRE((lst_not_copy == lst) == false);
        }
    }
}