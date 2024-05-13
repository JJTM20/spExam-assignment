//
// Created by jjtor on 06/05/2024.
//

#ifndef EKSAMENSPROJEKT_MOLECULE_H
#define EKSAMENSPROJEKT_MOLECULE_H
#include <stdlib.h>
#include <string>

class Molecule {
private:
    double current_amount;
public:
    std::string Symbol;
    double get_current_amount(){return current_amount;}
};


#endif //EKSAMENSPROJEKT_MOLECULE_H
