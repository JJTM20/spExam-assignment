//
// Created by jjtor on 30/05/2024.
//

#ifndef EKSAMENSPROJEKT_VESSEL_H
#define EKSAMENSPROJEKT_VESSEL_H


#include "GlobalState.h"

class Vessel {
private:
    std::string name;
    std::list<Reaction> reactions;
public:
    Vessel(std::string n){name = n;}
    GlobalState global_state; //Environment

    Molecule add(std::string name, double amount){
        auto molecule = Molecule(name, amount);
        global_state.AddReactant(molecule);
        return molecule;
    };
    void add(const Reaction reaction){
        //global_state.AddTime(reaction.get_current_rate_parameter());
        reactions.push_back(reaction);
    };
};


#endif //EKSAMENSPROJEKT_VESSEL_H
