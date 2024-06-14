//
// Created by jjtor on 11/06/2024.
//

#ifndef EKSAMENSPROJEKT_BENCHMARKER_H
#define EKSAMENSPROJEKT_BENCHMARKER_H

#include "bits/stdc++.h"

class Bench {
public:
    void start_clock(std::string name);
    void stop_clock(std::string name);
    void report();
private:
    struct tp {
        std::string name;
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;
    };
    std::vector<tp> storage;
};

#endif //EKSAMENSPROJEKT_BENCHMARKER_H
