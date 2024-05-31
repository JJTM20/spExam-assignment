cmake_minimum_required(VERSION 3.27)
project(Eksamensprojekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(Eksamensprojekt main.cpp
        StochasticSimulation.h
        Molecule.h
        Reaction.h
        StochasticSimulation.cpp
        PrettyPrinter.cpp
)
