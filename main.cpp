#include <iostream>
#include "Vessel.h"
#include "Molecule.h"
#include "StochasticSimulation.h"
#include "PrettyPrinter.h"
#include "Grapher.h"
#include "Benchmarker.h"

void HospitalPeak();
stochastic::Vessel circadian_rhythm();
stochastic::Vessel seihr(uint32_t N);
stochastic::Vessel Figure1_1();
stochastic::Vessel Figure1_2();
stochastic::Vessel Figure1_3();


int main() {
    //Vessels
    auto c = circadian_rhythm();
    auto s = seihr(10000);
    auto f1 = Figure1_1();
    auto f2 = Figure1_2();
    auto f3 = Figure1_3();
    //std::cout << c.GetReactions();

    //auto grapher = Grapher("Seihr");
    //grapher.Graph(r);
    //grapher.Graph(s.GetReactions());

    auto benchmarker = Bench();

    auto sim = stochastic::StochasticSimulation();
    //sim.RunSimulation(f3, 2000);
    //sim.RunSimulation(c, 100);
    //sim.RunSimulation(s, 100);
    //HospitalPeak();

#pragma region Single Run 50 Simulations Benchmarking
    /*benchmarker.start_clock("SEIHR_SINGLE");
    for (int i = 0; i < 50; ++i) {
        std::cout << "\n" << "i = " << i;
        sim.RunSimulation(s, 100);
    }
    benchmarker.stop_clock("SEIHR_SINGLE");
    std::cout << "\n";
    benchmarker.report();*/
#pragma endregion
#pragma region Parallel Run 50 Simulations Benchmarking
    benchmarker.start_clock("SEIHR_PARALLEL");
    sim.RunSimulationParallel(s, 100, 50);
    benchmarker.stop_clock("SEIHR_PARALLEL");
    benchmarker.report();
#pragma endregion

    std::cout << "\nHello, World!" << std::endl;

    return 0;
}

//Vessels
stochastic::Vessel circadian_rhythm(){
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


    auto v = stochastic::Vessel{"Circadian Rhythm"};

    const auto env = v.global_state.environment;

    const auto DA = v.add("DA", 1);
    const auto D_A = v.add("D_A", 0);
    const auto DR = v.add("DR", 1);
    const auto D_R = v.add("D_R", 0);
    const auto MA = v.add("MA", 0);
    const auto MR = v.add("MR", 0);
    const auto A = v.add("A", 0);
    const auto R = v.add("R", 0);
    const auto C = v.add("C", 0);


    v.add((A + DA) >> gammaA >>= D_A);
    v.add(D_A >> thetaA >>= DA + A);
    v.add((A + DR) >> gammaR >>= D_R);
    v.add(D_R >> thetaR >>= DR + A);
    v.add(D_A >> alpha_A >>= MA + D_A);
    v.add(DA >> alphaA >>= MA + DA);
    v.add(D_R >> alpha_R >>= MR + D_R);
    v.add(DR >> alphaR >>= MR + DR);
    v.add(MA >> betaA >>= MA + A);
    v.add(MR >> betaR >>= MR + R);
    v.add((A + R) >> gammaC >>= C);
    v.add(C >> deltaA >>= R);
    v.add(A >> deltaA >>= env);
    v.add(R >> deltaR >>= env);
    v.add(MA >> deltaMA >>= env);
    v.add(MR >> deltaMR >>= env);

    return v;
}
stochastic::Vessel seihr(uint32_t N) {

     auto v = stochastic::Vessel{"COVID19 SEIHR: " + std::to_string(N)};
     const auto eps = 0.0009; // initial fraction of infectious
     const auto I0 = size_t(std::round(eps * N)); // initial infectious
     const auto E0 = size_t(std::round(eps * N * 15)); // initial exposed
     const auto S0 = N - I0 - E0; // initial susceptible
     const auto R0 = 2.4;
     const auto alpha = 1.0 / 5.1; // incubation rate (E -> I) ~5.1 days
     const auto gamma = 1.0 / 3.1; // recovery rate (I -> R) ~3.1 days
     const auto beta = R0 * gamma; // infection/generation rate (S+I -> E+I)
     const auto P_H = 0.9e-3; // probability of hospitalization
     const auto kappa = gamma * P_H * (1.0 - P_H); // hospitalization rate (I -> H)
     const auto tau = 1.0 / 10.12; // removal rate in hospital (H -> R) ~10.12 days
     const auto S = v.add("S", S0); // susceptible
     const auto E = v.add("E", E0); // exposed
     const auto I = v.add("I", I0); // infectious
     const auto H = v.add("H", 0); // hospitalized
     const auto R = v.add("R", 0); // removed/immune (recovered + dead)
     v.add((S + I) >> beta / N >>= E + I); // susceptible becomes exposed by infectious
     v.add(E >> alpha >>= I); // exposed becomes infectious
     v.add(I >> gamma >>= R); // infectious becomes removed
     v.add(I >> kappa >>= H); // infectious becomes hospitalized
     v.add(H >> tau >>= R); // hospitalized becomes removed
     return v;
 }
stochastic::Vessel Figure1_1(){
    auto v = stochastic::Vessel("Fig1_1");
    const auto env = v.global_state.environment;
    const auto A = v.add("A", 100);
    const auto B = v.add("B", 0);
    const auto C = v.add("C", 1);
    const auto lambda = 0.001;
    v.add((A + C) >> lambda >>= B + C);
    return v;
}
stochastic::Vessel Figure1_2(){
    auto v = stochastic::Vessel("Fig1_2");
    const auto env = v.global_state.environment;
    const auto A = v.add("A", 100);
    const auto B = v.add("B", 0);
    const auto C = v.add("C", 2);
    const auto lambda = 0.001;
    v.add((A + C) >> lambda >>= B + C);
    return v;
}
stochastic::Vessel Figure1_3(){
    auto v = stochastic::Vessel("Fig1_3");
    const auto env = v.global_state.environment;
    const auto A = v.add("A", 50);
    const auto B = v.add("B", 50);
    const auto C = v.add("C", 1);
    const auto lambda = 0.001;
    v.add((A + C) >> lambda >>= B + C);
    return v;
}



void HospitalPeak(){
    auto observer = [](double time, stochastic::Vessel &v){
        static int max = 0;
        auto hospitalized = v.global_state.symbolTable.LookUp("H")->second;
        std::cout << "CURRENT HOSPITALIZED: " << hospitalized << "\n";
        if (hospitalized > max){
            max = hospitalized;
            std::cout << "New Peak Hospitalized: " << max << "\n";
        }
    };

    auto NDK = 5822763;
    auto NNJ = 589755;
    std::vector<int> pops = {NDK, NNJ};
    for (auto p:pops) {
        auto vessel = seihr(p);
        auto sim = stochastic::StochasticSimulation();
        sim.RunSimulation(vessel, 100, observer);
    }

}