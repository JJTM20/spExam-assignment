//
// Created by jjtor on 30/05/2024.
//

#ifndef EKSAMENSPROJEKT_REACTION_H
#define EKSAMENSPROJEKT_REACTION_H

#include <bits/stdc++.h>
#include "Molecule.h"

class Environment{
    Environment();
};

class Reaction{
private:
    std::vector<Molecule> reactants;
    double rate_parameter;
public:
    double get_current_rate_parameter(){return rate_parameter;}
    void set_rate_parameter(double rp){rate_parameter = rp;}
    std::vector<Molecule> get_reactants(){return reactants;}
};


#endif //EKSAMENSPROJEKT_REACTION_H
