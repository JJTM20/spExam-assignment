//
// Created by jjtor on 30/05/2024.
//

#ifndef EKSAMENSPROJEKT_REACTION_H
#define EKSAMENSPROJEKT_REACTION_H

#include <bits/stdc++.h>


class Environment{
    Environment();
};

class Molecule;

class Reaction{
private:
    std::vector<Molecule> reactants;
    double rate_parameter;
public:
    Reaction();
    double get_current_rate_parameter(){return rate_parameter;}
    void set_rate_parameter(double rp){rate_parameter = rp;}
    std::vector<Molecule> get_reactants(){return reactants;}
    void add_reactant(Molecule reactant){reactants.push_back(reactant);}
    void add_product(Molecule product){reactants.push_back(product);}


    //Overloads
    Reaction operator>>(double delay);

    Reaction operator>>=(Molecule molecule){
        add_product(molecule);
        return *this;
    };

    Reaction operator>>=(Reaction reaction);

};


#endif //EKSAMENSPROJEKT_REACTION_H
