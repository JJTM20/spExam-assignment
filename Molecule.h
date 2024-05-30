//
// Created by jjtor on 06/05/2024.
//

#ifndef EKSAMENSPROJEKT_MOLECULE_H
#define EKSAMENSPROJEKT_MOLECULE_H
#include <stdlib.h>
#include <string>
#include "Reaction.h"

class Molecule {
private:
    std::string symbol;
    double current_amount;
public:
    Molecule(std::string name, double amount){symbol = name, current_amount = amount;}
    double get_current_amount() { return current_amount; }

    void set_current_amount(double val) { current_amount = val; }

    //Overloads
    Reaction operator+(Molecule molecule) const{

    };
    Reaction operator+(Reaction reaction);


};


#endif //EKSAMENSPROJEKT_MOLECULE_H
