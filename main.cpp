#include <iostream>
#include "Vessel.h"
#include "Molecule.h"
#include "StochasticSimulation.h"


Vessel circadian_rhythm();

int main() {

    auto c = circadian_rhythm();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

Vessel circadian_rhythm(){
    const auto alphaA = 50;
    const auto alpha_A = 500;
    const auto alphaR = 0.01;
    const auto alpha_R = 50;
    const auto betaA = 50;
    const auto betaR = 5;
    const auto gammaA = 1;
    const auto gammaR = 1;
    const auto gammaC = 2;
    const auto deltaA = 1;
    const auto deltaR = 0.2;
    const auto deltaMA = 10;
    const auto deltaMR = 0.5;
    const auto thetaA = 50;
    const auto thetaR = 100;


    auto v = Vessel{"Circadian Rhythm"};

    const auto environment = v.global_state.environment;

    const auto D_A = v.add("D_A", 0);
    const auto A = v.add("A", 0);
    const auto DA = v.add("DA", 1);

    v.add((A + DA) >> gammaA >>= D_A);

    return v;
}