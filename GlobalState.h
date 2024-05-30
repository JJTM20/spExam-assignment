//
// Created by jjtor on 30/05/2024.
//

#ifndef EKSAMENSPROJEKT_GLOBALSTATE_H
#define EKSAMENSPROJEKT_GLOBALSTATE_H

#include <bits/stdc++.h>
#include "Molecule.h"
#include "Reaction.h"


class GlobalState {
private:
    double time = 0;
    std::list<Molecule> reactants; //Current molecules swimming around
    std::map<std::string, int> generic_lookup_table;

public:
    GlobalState();

    Environment environment;
    void AddReactant(Molecule reactant){reactants.push_back(reactant);}

    void AddTime(double time_to_add) { time += time_to_add; }

    double GetCurrentTime() { return time; }

    std::string LookUp(std::string molecule_to_find) {
        auto it = generic_lookup_table.find(molecule_to_find);
        return it->first;
    }
};


#endif //EKSAMENSPROJEKT_GLOBALSTATE_H
