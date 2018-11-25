#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <iostream>
#include "laser.hpp"


TEST_CASE("test provided 1") {
    stringstream in("7 9\n"
                    "0 1  8  7  2  2\n"
                    "0 2  1  5  1  2\n"
                    "1 3  6 16  5  5\n"
                    "2 3  4 12 18 10\n"
                    "3 6 10  8 13  4\n"
                    "4 1 13  6 10 16\n"
                    "5 3  2 11  4  2\n"
                    "5 6  4  6  6  1\n"
                    "6 2 12 15 24  5");

    vector<node> actual;
    vector<node> expected = {0, 2, 3, 5, 6};
    REQUIRE(24 == laser(in, back_inserter(actual)));
    REQUIRE(expected == actual);
}

TEST_CASE("test provided 2") {
    stringstream in("10 10\n"
                    "0 6 1 0 1000000 1\n"
                    "1 0 1 0 1000000 1\n"
                    "2 5 1 0 1000000 1\n"
                    "2 7 1 0 1000000 1\n"
                    "3 4 1 0 1000000 1\n"
                    "4 1 1 0 1000000 1\n"
                    "4 5 1 0 1000000 1\n"
                    "4 9 1 0 1000000 1\n"
                    "7 5 1 0 1000000 1\n"
                    "7 6 1 0 1000000 1");

    vector<node> actual;
    vector<node> expected = {0, 1, 4, 9};
    REQUIRE(3 == laser(in, back_inserter(actual)));
    REQUIRE(expected == actual);
}