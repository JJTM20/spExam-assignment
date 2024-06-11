//
// Created by jjtor on 06/05/2024.
//

#include "StochasticSimulation.h"
#include "GlobalState.h"
#include "Molecule.h"
#include "Reaction.h"

//Global variables


//Prototypes
Reaction FindSmallestDelayReaction(Vessel& vessel);
double RandomNumberGen(double delay){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<double> distribution(delay);
    double d = distribution(gen);
    return d;
}

void StochasticSimulation::RunSimulation(Vessel vessel, double end_time) {
    std::string mCount;
    std::string header;
    this->path = "..\\out\\trajectory_" + vessel.GetName() + ".csv";
    trajectory = std::ofstream(path);
    header += "Time,";
    trajectory << header;
    for (auto it = vessel.global_state.symbolTable.table.begin(); it != vessel.global_state.symbolTable.table.end(); ++it){
        if (std::next(it) != vessel.global_state.symbolTable.table.end()){
            trajectory << it->first << ",";
        }else{
            trajectory << it->first << "\n";
        }
    }
    std::cout << "Running simulation. Time: "  + std::to_string(vessel.global_state.GetCurrentTime()) + "\n";

    while (vessel.global_state.GetCurrentTime() <= end_time){
        for (const auto& [key, value] : vessel.global_state.symbolTable.table) {
            mCount += std::to_string(value) + ",";
        }
        mCount.pop_back();
        trajectory << vessel.global_state.GetCurrentTime() << ',' << mCount;
        trajectory << "\n";
        mCount.clear();
        for (auto &r : vessel.GetReactions()) {
            auto delay = ComputeReactionTime(r, vessel);
            r.set_delay(delay);
             //Fix so it is taken directly from symbol table without for-range loop
        }

        // Pick reaction with shortest delay (reaction time)
        auto min_delay_reaction = FindSmallestDelayReaction(vessel);

        vessel.global_state.AddTime(min_delay_reaction.get_current_delay()); //Line 5
        for (auto &q : min_delay_reaction.get_reactants()) {
            if (std::all_of(min_delay_reaction.get_reactants().begin(), min_delay_reaction.get_reactants().end(), [&](Molecule& i) { return vessel.global_state.symbolTable.LookUp(i.GetName())->second > 0; })){
                //TODO: Implement lookup/symbol table (To be..)
                vessel.global_state.symbolTable.Update(q.GetName(), -1);
            }
        }
        for (auto &p:min_delay_reaction.get_products()) {
            vessel.global_state.symbolTable.Update(p.GetName(), 1);
        }
    std::cout << "Simulation step done. Time: "  + std::to_string(vessel.global_state.GetCurrentTime()) + "\n";
    }
    std::cout << "Simulation done. Time: "  + std::to_string(vessel.global_state.GetCurrentTime());

}

double StochasticSimulation::ComputeReactionTime(Reaction& reaction, Vessel& vessel){
    double total_amount_of_reactants = 1.0;
    for (const auto &m:reaction.get_reactants()){
        if (vessel.global_state.symbolTable.LookUp(m.GetName())->second <= 0){
            return std::numeric_limits<double>::infinity();
        }
        total_amount_of_reactants *= vessel.global_state.symbolTable.LookUp(m.GetName())->second;
    }
    return RandomNumberGen(reaction.get_current_rate_parameter() * total_amount_of_reactants);
}

Reaction FindSmallestDelayReaction(Vessel& vessel){
    auto min_delay = std::numeric_limits<double>::infinity();
    auto min_delay_reaction = Reaction();
    for (auto& r : vessel.GetReactions()) {
        if (r.get_current_delay() < min_delay){
            min_delay = r.get_current_delay();
            min_delay_reaction = r;
        }
    }
    if (min_delay <= 0.000001){
        std::cout << "Error: " << min_delay_reaction.get_current_delay() << "\n";
    }
    std::cout << "Min_delay: " << min_delay_reaction.get_current_delay() << "\n";
    return min_delay_reaction;
}


Reaction Molecule::operator+(Molecule molecule) const {
    auto r = Reaction();
    r.add_reactant(molecule);
    r.add_reactant(*this);
    return r;
}


Reaction Molecule::operator>>(double rate) const{
    auto r = Reaction();
    r.add_reactant(*this);
    r.set_rate_parameter(rate);
    return r;
}

Reaction Molecule::operator+(Reaction reaction) {
    auto r = Reaction();
    for (auto &reactant:reaction.get_reactants()) {
        r.add_reactant(reactant);
    }
    for (auto &product:reaction.get_products()) {
        r.add_product(product);
    }
    r.set_rate_parameter(reaction.get_current_rate_parameter());
    return r;
};