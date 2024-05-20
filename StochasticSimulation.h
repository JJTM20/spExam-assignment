//
// Created by jjtor on 06/05/2024.
//

#ifndef EKSAMENSPROJEKT_STOCHASTICSIMULATION_H
#define EKSAMENSPROJEKT_STOCHASTICSIMULATION_H

#include <bits/stdc++.h>
#include "Molecule.h"
#include <chrono>
#include <functional>

class Reaction{
private:
    std::vector<Molecule> reactants;
    double rate_parameter;
public:
    double get_current_rate_parameter(){return rate_parameter;}
    void set_rate_parameter(double rp){rate_parameter = rp;}
    std::vector<Molecule> get_reactants(){return reactants;}
};

class GlobalState{
private:
    double time = 0;
    std::list<std::pair<Molecule, int>> reactant_amounts;
public:
    std::list<Reaction> reactions;
    void AddTime(double time_to_add){time += time_to_add;}
    double GetCurrentTime(){return time;}
};

class StochasticSimulation {
public:
    void RunSimulation(std::vector<Reaction> reaction_set, double end_time, GlobalState state);
    const double ComputeReactionTime(Reaction reaction);
};


#endif //EKSAMENSPROJEKT_STOCHASTICSIMULATION_H
