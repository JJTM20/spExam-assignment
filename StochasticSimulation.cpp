//
// Created by jjtor on 06/05/2024.
//

#include "StochasticSimulation.h"

//Prototypes
const std::chrono::duration<double, std::milli> ComputeDelay();

void StochasticSimulation::RunSimulation(std::vector<Reaction> reaction_set, std::chrono::time_point<std::chrono::high_resolution_clock> end_time, GlobalState state) {
    const std::chrono::time_point<std::chrono::high_resolution_clock> t = std::chrono::high_resolution_clock::now();
    while (t <= end_time){
        for (auto r : reaction_set) {
            auto delay = ComputeDelay(); //TODO: Implement so that the delay is tied to the reaction object
        }
    }
}

const std::chrono::duration<double, std::milli> StochasticSimulation::ComputeReactionTime(Reaction reaction){
    std::vector<Molecule> reactants = reaction.get_reactants();
    double total_amount_of_reactants;
    for (auto m:reactants) {
        total_amount_of_reactants += m.get_current_amount();
    }
    double r_delay = reaction.get_current_rate_parameter() * total_amount_of_reactants;
    return new std::chrono::durationr_delay;
}

long RandomNumberGen(double delay){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<double> distribution(delay);
}