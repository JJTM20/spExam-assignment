//
// Created by jjtor on 06/05/2024.
//

#include "StochasticSimulation.h"
#include "GlobalState.h"
#include "Molecule.h"
#include "Reaction.h"

//Global variables


//Prototypes
const Reaction FindSmallestDelayReaction(GlobalState global_state);

void StochasticSimulation::RunSimulation(std::vector<Reaction> reaction_set, double end_time, GlobalState global_state) {
    while (global_state.GetCurrentTime() <= end_time){
        for (auto r : reaction_set) {
            auto delay = ComputeReactionTime(r); //TODO: Implement so that the delay is tied to the reaction object (DONE)
            r.set_rate_parameter(delay);
        }

        // Pick reaction with shortest delay (reaction time)
        auto min_delay_reaction = FindSmallestDelayReaction(global_state);

        global_state.AddTime(min_delay_reaction.get_current_rate_parameter());
        for (auto q : min_delay_reaction.get_reactants()) {
            if (q.get_current_amount() > 0){
                //TODO: Implement lookup table (DONE)
                q.set_current_amount(q.get_current_amount() - 1);
            }
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

const Reaction FindSmallestDelayReaction(GlobalState global_state){
    auto min_delay_reaction = Reaction();
    min_delay_reaction.set_rate_parameter(std::numeric_limits<double>::infinity());/*
    for (auto r : global_state.reactions) {
        if (r.get_current_rate_parameter() < min_delay_reaction.get_current_rate_parameter()){
            min_delay_reaction = r;
        }
    }*/
    return min_delay_reaction;
}


void RandomNumberGen(double delay){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<double> distribution(delay);
}


Reaction Molecule::operator+(Molecule molecule) const {
    auto r = Reaction();
    r.add_reactant(molecule);
    r.add_reactant(*this);
    return r;
}


Reaction Molecule::operator>>(double delay) const{
    auto r = Reaction();
    r.add_reactant(*this);
    r.set_rate_parameter(delay); //Delay = rate_parameter
    return r;
}

Reaction Molecule::operator+(Reaction reaction) {
    auto r = Reaction();
    for (auto reactant:reaction.get_reactants()) {
        r.add_reactant(reactant);
    }
    for (auto product:reaction.get_products()) {
        r.add_product(product);
    }
    return r;
};

