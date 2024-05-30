//
// Created by jjtor on 06/05/2024.
//

#ifndef EKSAMENSPROJEKT_STOCHASTICSIMULATION_H
#define EKSAMENSPROJEKT_STOCHASTICSIMULATION_H

#include <bits/stdc++.h>
#include "Molecule.h"
#include <chrono>
#include <functional>
#include <algorithm>
#include "Reaction.h"
#include "GlobalState.h"
#include "Vessel.h"


class StochasticSimulation {
private:

public:
    void RunSimulation(std::vector<Reaction> reaction_set, double end_time, GlobalState state);
    const double ComputeReactionTime(Reaction reaction);
};


#endif //EKSAMENSPROJEKT_STOCHASTICSIMULATION_H
