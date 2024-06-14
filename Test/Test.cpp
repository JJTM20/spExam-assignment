//
// Created by jjtor on 12/06/2024.
//

#include "doctest.h"
#include "../StochasticSimulation.h"

int fact(int n) {
    return n <= 1 ? n : fact(n - 1) * n;
}
TEST_CASE("testing the factorial function") {
    CHECK(fact(1) == 1);
    CHECK(fact(2) == 2);
    CHECK(fact(3) == 6);
    CHECK(fact(10) == 3628800);
}