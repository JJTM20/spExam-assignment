//
// Created by jjtor on 06/05/2024.
//

#include "StochasticSimulation.h"

//Global variables
auto global_state = GlobalState();

//Prototypes
const Reaction FindSmallestDelayReaction();

void StochasticSimulation::RunSimulation(std::vector<Reaction> reaction_set, double end_time, GlobalState state) {
    //const std::chrono::time_point<std::chrono::high_resolution_clock> t = std::chrono::high_resolution_clock::now();

    while (global_state.GetCurrentTime() <= end_time){
        for (auto r : reaction_set) {
            auto delay = ComputeReactionTime(r); //TODO: Implement so that the delay is tied to the reaction object
            r.set_rate_parameter(delay);
        }

        // Pick reaction with shortest delay (reaction time)
        auto min_delay_reaction = FindSmallestDelayReaction();

        global_state.AddTime(min_delay_reaction.get_current_rate_parameter());
        for (auto q : min_delay_reaction.get_reactants()) {
            //Implement lookup table
        }
    }
}

const double StochasticSimulation::ComputeReactionTime(Reaction reaction){
    std::vector<Molecule> reactants = reaction.get_reactants();
    double total_amount_of_reactants;
    for (auto m:reactants){
        total_amount_of_reactants += m.get_current_amount();
    }
    double r_delay = reaction.get_current_rate_parameter() * total_amount_of_reactants;
    return r_delay;
}

const Reaction FindSmallestDelayReaction(){
    auto min_delay_reaction = Reaction();
    min_delay_reaction.set_rate_parameter(std::numeric_limits<double>::infinity());
    for (auto r : global_state.reactions) {
        if (r.get_current_rate_parameter() < min_delay_reaction.get_current_rate_parameter()){
            min_delay_reaction = r;
        }
    }
}


long RandomNumberGen(double delay){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<double> distribution(delay);
}
