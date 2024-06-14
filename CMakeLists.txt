cmake_minimum_required(VERSION 3.27)
project(Eksamensprojekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(Eksamensprojekt main.cpp
        StochasticSimulation.h
        Molecule.h
        Reaction.h
        StochasticSimulation.cpp
        PrettyPrinter.cpp
        Grapher.h
        Benchmarker.cpp
)

enable_testing()
include(Test/doctest.cmake)
add_executable(tests Test/Test.cpp StochasticSimulation.cpp StochasticSimulation.h)
target_link_libraries(tests PRIVATE doctest::doctest_with_main)