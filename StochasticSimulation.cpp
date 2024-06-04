//
// Created by jjtor on 06/05/2024.
//

#include "StochasticSimulation.h"
#include "GlobalState.h"
#include "Molecule.h"
#include "Reaction.h"

//Global variables


//Prototypes
const Reaction FindSmallestDelayReaction(Vessel vessel);
double RandomNumberGen(double delay){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<> distribution(delay);
    return distribution(gen);
}

void StochasticSimulation::RunSimulation(Vessel vessel, double end_time) {
    std::cout << "Running simulation. Time: "  + std::to_string(vessel.global_state.GetCurrentTime());
    while (vessel.global_state.GetCurrentTime() <= end_time){
        for (auto &r : *vessel.GetReactions()) {
            auto delay = ComputeReactionTime(&r);
            r.set_rate_parameter(delay);
        }
        // Pick reaction with shortest delay (reaction time)
        auto min_delay_reaction = FindSmallestDelayReaction(vessel);

        vessel.global_state.AddTime(min_delay_reaction.get_current_rate_parameter()); //Line 5
        for (auto q : min_delay_reaction.get_reactants()) {
            if (q.get_current_amount() > 0){
                //TODO: Implement lookup/symbol table (DONE)
                q.set_current_amount(q.get_current_amount() - 1);
                for (auto p:min_delay_reaction.get_products()) {
                    p.set_current_amount(p.get_current_amount() + 1);
                }
            }
        }
    std::cout << "Simulation step done. Time: "  + std::to_string(vessel.global_state.GetCurrentTime()) + "\n";
    }
    std::cout << "Simulation done. Time: "  + std::to_string(vessel.global_state.GetCurrentTime());

}

const double StochasticSimulation::ComputeReactionTime(Reaction* reaction){
    std::vector<Molecule> reactants = reaction->get_reactants();
    double total_amount_of_reactants = 1;
    for (auto m:reactants){
        total_amount_of_reactants *= m.get_current_amount();
    }
    double r_delay = RandomNumberGen(reaction->get_current_rate_parameter() * total_amount_of_reactants);
    return r_delay;
}

const Reaction FindSmallestDelayReaction(Vessel vessel){
    auto min_delay_reaction = Reaction();
    min_delay_reaction.set_rate_parameter(std::numeric_limits<double>::infinity());
    for (auto r : *vessel.GetReactions()) {
        if (r.get_current_rate_parameter() < min_delay_reaction.get_current_rate_parameter()){
            min_delay_reaction = r;
        }
    }
    return min_delay_reaction;
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
    r.set_rate_parameter(reaction.get_current_rate_parameter());
    return r;
};