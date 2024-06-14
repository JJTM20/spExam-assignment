//
// Created by jjtor on 14/06/2024.
//
#include "Benchmarker.h"
#include <iostream>

void Bench::start_clock(std::string name) {
    tp timepoint;
    timepoint.name = name;
    timepoint.start = std::chrono::high_resolution_clock::now();
    storage.push_back(timepoint);
}
void Bench::stop_clock(std::string name) {
    for (auto &v : storage){
        if (v.name == name){
            v.end = std::chrono::high_resolution_clock::now();
            return;
        }
    }
}

void Bench::report() {
    for (auto &v : storage){
        std::chrono::duration<double, std::milli> duration;
        duration = v.end - v.start;
        std::cout << v.name << " took " << duration.count() << " ms";
    }
}